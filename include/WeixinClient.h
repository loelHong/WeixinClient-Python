#include "client.h"
#include <functional>

struct Friend {
	std::string wxid;
	std::string wxnum;
	std::string nickname;
	std::string remark;
	MSGPACK_DEFINE(wxid, wxnum, nickname, remark);
};

struct SelfInfo {
	std::string wxid;
	std::string wxnum;
	std::string nickname;
	std::string signature;
	std::string big_avatar;
	std::string small_avatar;
	std::string nation;
	std::string province;
	std::string city;
	std::string phone_number;
	MSGPACK_DEFINE(wxid, wxnum, nickname, signature, big_avatar, small_avatar, nation, province, city, phone_number);
};

struct UserInfo {
	std::string wxid;
	std::string wxnum;
	std::string v3;
	std::string remark;
	std::string nickname;
	std::string big_avatar;
	std::string small_avatar;
	std::string signature;
	std::string nation;
	std::string province;
	std::string city;
	std::string background;
	MSGPACK_DEFINE(wxid, wxnum, v3, remark, nickname, big_avatar, small_avatar, signature, nation, province, city, background);
};

struct ChatRoomInfo
{
    std::string v3;
    std::string wxid;
    std::string name;
    std::string remark;
    std::string avatar;
    MSGPACK_DEFINE(wxid, v3, name, remark, avatar);
};


class WeixinClient
{
public:
	WeixinClient():WeixinClient("127.0.0.1"){}

	WeixinClient(std::string ip):WeixinClient(ip, 10086){}

	WeixinClient(std::string ip, int port1):WeixinClient(ip, port1, 100010){}

	WeixinClient(std::string ip, int port1, int port2){
		m_client = std::make_shared<Client>(ip, port1, port2);
	}
	~WeixinClient() {
	}

	void login(std::function<void(std::string)> qrcode = [](std::string url) -> void {});

	bool is_login();

	std::string get_QRCodeURL();

	void show_QRCode();

	SelfInfo get_self_info();

	UserInfo get_user_by_wxid(std::wstring wxid);

	std::vector<Friend> get_friend_list();

	std::string get_nickname_by_wxid(std::wstring wxid);

    std::string get_self_wxid();

    int send_text(std::wstring wxid, std::wstring text);

	int send_image(std::wstring wxid, std::wstring image_path);

	int call_a8key(std::wstring wxid, std::wstring url);

	int send_file(std::wstring wxid, std::wstring file_path);

	int send_xml_article(std::wstring wxid, std::wstring xml);

	int send_article(std::wstring wxid, std::wstring title, std::wstring abstract, std::wstring url);

	int send_card(std::wstring wxid, std::wstring share_wxid);

	int send_at_text(std::wstring chatroomid, std::wstring at_text);

	int add_friend(int sztype, std::wstring wxid, std::wstring message);

	int agree_friend_request(std::wstring v3, std::string v4);

	int find_stranger(std::wstring mobile);

	std::vector<std::wstring> get_chatroom_member_list(std::wstring chatroomid);

	int add_chatroom_memeber(std::wstring chatroomid, std::wstring wxid);

	ChatRoomInfo get_chatroom_info(std::wstring chatroomid);

	void subscribe(std::string topic);

	void unsubscribe(std::string topic);

	std::string recieve_message(int flag);

private:
	std::shared_ptr<Client> m_client;

};




