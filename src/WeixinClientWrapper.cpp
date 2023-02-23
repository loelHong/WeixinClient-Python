#include "WeixinClient.h"
#include <pybind11/stl.h>
#include "pybind11/pybind11.h"
#include "pybind11/functional.h"

namespace py = pybind11;
PYBIND11_MODULE(WexinClient_Python, m) {
	pybind11::class_<Friend>(m, "Friend")
		.def(py::init<>())
		.def_readonly("wxid", &Friend::wxid)
		.def_readonly("wxnum", &Friend::wxnum)
		.def_readonly("nickname", &Friend::nickname)
		.def_readonly("remark", &Friend::remark)
		.def("to_json",
            [](const Friend &a) {
		        std::map<std::string, std::string> ret;
                ret["wxid"] = a.wxid;
                ret["wxnum"] = a.wxnum;
                ret["nickname"] = a.nickname;
                ret["remark"] = a.remark;
                return ret;
            }
        );
	pybind11::class_<SelfInfo>(m, "SelfInfo")
		.def(py::init<>())
		.def_readonly("wxid", &SelfInfo::wxid)
		.def_readonly("wxnum", &SelfInfo::wxnum)
		.def_readonly("nickname", &SelfInfo::nickname)
		.def_readonly("signature", &SelfInfo::signature)
		.def_readonly("big_avatar", &SelfInfo::big_avatar)
		.def_readonly("small_avatar", &SelfInfo::small_avatar)
		.def_readonly("nation", &SelfInfo::nation)
		.def_readonly("province", &SelfInfo::province)
		.def_readonly("city", &SelfInfo::city)
		.def_readonly("phone_number", &SelfInfo::phone_number)
		.def("to_json",
            [](const SelfInfo &a) {
		        std::map<std::string, std::string> ret;
                ret["wxid"] = a.wxid;
                ret["wxnum"] = a.wxnum;
                ret["nickname"] = a.nickname;
                ret["signature"] = a.signature;
                ret["big_avatar"] = a.big_avatar;
                ret["small_avatar"] = a.small_avatar;
                ret["nation"] = a.nation;
                ret["province"] = a.province;
                ret["city"] = a.city;
                ret["phone_number"] = a.phone_number;
                return ret;
            }
        );

    pybind11::class_<ChatRoomInfo>(m, "ChatRoomInfo")
            .def(py::init<>())
            .def_readonly("v3", &ChatRoomInfo::v3)
            .def_readonly("wxid", &ChatRoomInfo::wxid)
            .def_readonly("name", &ChatRoomInfo::name)
            .def_readonly("remark", &ChatRoomInfo::remark)
            .def_readonly("avatar", &ChatRoomInfo::avatar)
            .def("to_json",
                 [](const ChatRoomInfo &a) {
                     std::map<std::string, std::string> ret;
                     ret["v3"] = a.v3;
                     ret["wxid"] = a.wxid;
                     ret["name"] = a.name;
                     ret["remark"] = a.remark;
                     ret["avatar"] = a.avatar;
                     return ret;
                 }
            );

    pybind11::class_<UserInfo>(m, "UserInfo")
            .def(py::init<>())
            .def_readonly("wxid", &UserInfo::wxid)
            .def_readonly("wxnum", &UserInfo::wxnum)
            .def_readonly("v3", &UserInfo::v3)
            .def_readonly("nickname", &UserInfo::nickname)
            .def_readonly("big_avatar", &UserInfo::big_avatar)
            .def_readonly("small_avatar", &UserInfo::small_avatar)
            .def_readonly("signature", &UserInfo::signature)
            .def_readonly("nation", &UserInfo::nation)
            .def_readonly("province", &UserInfo::province)
            .def_readonly("city", &UserInfo::city)
            .def_readonly("background", &UserInfo::background)
            .def("to_json",
                 [](const UserInfo &a) {
                     std::map<std::string, std::string> ret;
                     ret["wxid"] = a.wxid;
                     ret["wxnum"] = a.wxnum;
                     ret["v3"] = a.v3;
                     ret["nickname"] = a.nickname;
                     ret["big_avatar"] = a.big_avatar;
                     ret["small_avatar"] = a.small_avatar;
                     ret["signature"] = a.signature;
                     ret["nation"] = a.nation;
                     ret["province"] = a.province;
                     ret["city"] = a.city;
                     ret["background"] = a.background;
                     return ret;
                 }
            );
	pybind11::class_<WeixinClient>(m, "WeixinClient")
		.def(py::init<>())
		.def(py::init<std::string>())
		.def(py::init<std::string, int>())
		.def(py::init<std::string, int, int>())
		.def("is_login", &WeixinClient::is_login)
		// .def("show_QRCode", &WeixinClient::show_QRCode)
		.def("get_QRCodeURL", &WeixinClient::get_QRCodeURL)
		.def("call_a8key", &WeixinClient::call_a8key)
		.def("add_friend", &WeixinClient::add_friend)
		.def("add_chatroom_memeber", &WeixinClient::add_chatroom_memeber)
		.def("agree_friend_request", &WeixinClient::agree_friend_request)
		.def("find_stranger", &WeixinClient::find_stranger)
		.def("get_chatroom_info", &WeixinClient::get_chatroom_info)
		.def("get_chatroom_member_list", &WeixinClient::get_chatroom_member_list)
		.def("get_friend_list", &WeixinClient::get_friend_list, py::return_value_policy::copy)
		.def("get_self_info", &WeixinClient::get_self_info, py::return_value_policy::copy)
		.def("get_nickname_by_wxid", &WeixinClient::get_nickname_by_wxid)
		.def("send_article", &WeixinClient::send_article)
		.def("send_xml_article", &WeixinClient::send_xml_article)
        .def("get_user_by_wxid", &WeixinClient::get_user_by_wxid)
        .def("get_self_wxid", &WeixinClient::get_self_wxid)
        .def("send_at_text", &WeixinClient::send_at_text)
		.def("send_card", &WeixinClient::send_card)
		.def("send_file", &WeixinClient::send_file)
		.def("send_image", &WeixinClient::send_image)
		.def("send_text", &WeixinClient::send_text)
		.def("subscribe", &WeixinClient::subscribe)
		.def("unsubscribe", &WeixinClient::unsubscribe)
		.def("recieve_message", &WeixinClient::recieve_message);
}
