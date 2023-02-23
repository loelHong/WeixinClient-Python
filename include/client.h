#include "zmq.h"
#include <string>
#include <iostream>
#include <msgpack.hpp>
#include <tuple>
#include <string>
#include <regex>
#include <mutex>

class Client : public std::enable_shared_from_this<Client> {

public:

    Client(std::string ip, int port1, int port2):endpoint1("tcp://" + ip + ":" + std::to_string(port1)), endpoint2("tcp://" + ip + ":" + std::to_string(port2)) {
		send_sock = zmq_socket(context, ZMQ_REQ);
		recv_sock = zmq_socket(context, ZMQ_SUB);
		zmq_connect(send_sock, endpoint1.c_str());
		zmq_connect(recv_sock, endpoint2.c_str());
		std::cout << "client connect" << std::endl;
    }
	~Client() {
		std::cout << "client disconnect" << std::endl;
		zmq_disconnect(send_sock, endpoint1.c_str());
		zmq_disconnect(recv_sock, endpoint2.c_str());
		zmq_close(recv_sock);
		zmq_close(send_sock);
		zmq_ctx_destroy(context);
	}


	void subscribe(const char* topic) {
		zmq_setsockopt(recv_sock, ZMQ_SUBSCRIBE, topic, strlen(topic));
	}

	void unsubscribe(const char* topic) {
		zmq_setsockopt(recv_sock, ZMQ_UNSUBSCRIBE, topic, strlen(topic));
	}

	char* recieve_message(int flags) {
        std::lock_guard<std::mutex> lock(recv_lock);
        return recv_data(recv_sock, flags);// ������
	}

	template<typename T, typename... Args>
	typename std::enable_if<!std::is_void<T>::value, T>::type call(const std::string& func, Args&&... args) {
		//���л�������
		msgpack::sbuffer method = pack(func);

		//�������, ����һ����tuple����
		msgpack::sbuffer params = pack(std::make_tuple(args...));

		char* method_data = method.data();
		char* params_data = params.data();
		std::size_t method_size = method.size();
		std::size_t params_size = params.size();

		auto pack_method_size = pack(method_size);
		auto pack_params_size = pack(params_size);

		std::size_t total_size = 8 + method_size + params_size;
		char* buffer = new char[total_size + 1];

		memcpy(buffer, pack_method_size.data(), 4);
		memcpy(buffer + 4, method_data, method_size);
		memcpy(buffer + 4 + method_size, pack_params_size.data(), 4);
		memcpy(buffer + 8 + method_size, params_data, params_size);
		buffer[total_size] = 0;
         std::lock_guard<std::mutex> lock(send_lock);
		send_data(send_sock, buffer, total_size + 1);

		int t;
		char* data = recv_data(send_sock, 0);// ����
        assert(data != nullptr);
		size_t flag = unpack<size_t>(data, 4, t);

		if (t) {
			//���紫�����ݳ����������Ƕ���֮���, ���쳣
			throw std::runtime_error("Network data transmission error");
		}
		if (flag != 0) {
			//����������Ϣ
			std::string err_msg = unpack<std::string>(data + 4, flag);
			//���쳣
			throw std::runtime_error(err_msg);
		}
		else {
			size_t len = unpack<size_t>(data + 4, 4);
			T res = unpack<T>(data + 8, len);
			return res;
		}
	}

private:
    void* send_sock;
	void* recv_sock;
    std::mutex send_lock;
    std::mutex recv_lock;
    void * context = zmq_ctx_new();

    std::string endpoint1 = "tcp://127.0.0.1:10086";
    std::string endpoint2 = "tcp://127.0.0.1:10010";

	template <typename T>
	msgpack::sbuffer pack(T &&t) {
		msgpack::sbuffer buffer;
		msgpack::pack(buffer, std::forward<T>(t));
		return buffer;
	}

	template<typename T>
	T unpack(const char* data, const size_t length) {
		try {
			msgpack::unpacked msg_;
			msgpack::unpack(msg_, data, length);
			return msg_.get().as<T>();
		}
		catch (...) {
			std::cout << "������ƥ��" << std::endl;
			return T();
		}
	}

	template<typename T>
	T unpack(const char* data, const size_t length, int& err) {
		try {
			msgpack::unpacked msg_;
			msgpack::unpack(msg_, data, length);
			err = 0;
			return msg_.get().as<T>();
		}
		catch (...) {
			err = 1;
			return T();
		}
	}

	int send_data(void* sock, const char* data, size_t len)
	{
		zmq_msg_t msg;
		zmq_msg_init_size(&msg, len);
		memcpy(zmq_msg_data(&msg), data, len);

		int rc = zmq_msg_send(&msg, sock, 0);
        assert(rc != -1);
		zmq_msg_close(&msg);

		return rc;
	}

	char* recv_data(void* sock, int flags)
	{
		zmq_msg_t message;
		zmq_msg_init(&message);

		int size = zmq_msg_recv(&message, sock, flags);
		if(size == -1){
		    return nullptr;
		}
		char* data = (char*)malloc(size + 1);
		memcpy(data, zmq_msg_data(&message), size);

		zmq_msg_close(&message);
		data[size] = 0;
		return data;
	}
};
