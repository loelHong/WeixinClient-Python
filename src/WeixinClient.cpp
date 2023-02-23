#include "WeixinClient.h"


void WeixinClient::show_QRCode() {

	//m_client->call<void>("show_QRCode");
}

int WeixinClient::call_a8key(std::wstring wxid, std::wstring url) {
	return m_client->call<int>("CallA8Key", wxid, url);
}

int WeixinClient::add_friend(int sztype, std::wstring wxid, std::wstring message) {
	return m_client->call<int>("AddFriend", sztype, wxid, message);
}

int WeixinClient::add_chatroom_memeber(std::wstring chatroomid, std::wstring wxid){
	return m_client->call<int>("AddChatRoomMember", chatroomid, wxid);
}

int WeixinClient::agree_friend_request(std::wstring v3, std::string v4) {
	return m_client->call<int>("AgreeFriendRequest", v3, v4);
}

int WeixinClient::send_text(std::wstring wxid, std::wstring text) {
	return m_client->call<int>("SendText", wxid, text);
}

int WeixinClient::find_stranger(std::wstring mobile) {
	return m_client->call<int>("FindStranger", mobile);
}

int WeixinClient::send_image(std::wstring wxid, std::wstring image_path) {
	return m_client->call<int>("SendImage", wxid, image_path);
}

int WeixinClient::send_file(std::wstring wxid, std::wstring file_path) {
	return m_client->call<int>("SendFile", wxid, file_path);
}

int WeixinClient::send_article(std::wstring wxid, std::wstring title, std::wstring abstract, std::wstring url) {
	return m_client->call<int>("SendArticle", wxid, title, abstract, url);
}

ChatRoomInfo WeixinClient::get_chatroom_info(std::wstring chatroomid) {
	return m_client->call<ChatRoomInfo>("GetChatRoomInfo", chatroomid);
}

int WeixinClient::send_card(std::wstring wxid, std::wstring share_wxid) {
	return m_client->call<int>("SendCard", wxid, share_wxid);
}

int WeixinClient::send_at_text(std::wstring chatroomid, std::wstring at_text) {
	return m_client->call<int>("SendAtText", chatroomid, at_text);
}

std::vector<std::wstring> WeixinClient::get_chatroom_member_list(std::wstring chatroomid) {
	return m_client->call<std::vector<std::wstring>>("GetChatRoomMemberList", chatroomid);
}

int WeixinClient::send_xml_article(std::wstring wxid, std::wstring xml) {
	return m_client->call<int>("SendXmlArticle", wxid, xml);
}

std::string WeixinClient::get_QRCodeURL() {
	return m_client->call<std::string>("GetQRCodeURL");
}

SelfInfo WeixinClient::get_self_info() {
	return m_client->call<SelfInfo>("GetSelfInfo");
}

std::string WeixinClient::get_self_wxid() {
    return m_client->call<std::string>("get_self_wxid");
}

std::string WeixinClient::get_nickname_by_wxid(std::wstring wxid) {
	UserInfo user = get_user_by_wxid(wxid);
	return user.nickname;
}

std::vector<Friend> WeixinClient::get_friend_list() {
	return m_client->call<std::vector<Friend>>("GetFriendList");
}

UserInfo WeixinClient::get_user_by_wxid(std::wstring wxid) {
	return m_client->call<UserInfo>("GetUserByWxid", wxid);
}

void WeixinClient::login(std::function<void(std::string)> qrcode)
{
	// std::string lastQRCodeURL;
	// while (!is_login()) {
	// 	std::string currQRCOdeURL = get_QRCodeURL();
	// 	if (currQRCOdeURL != lastQRCodeURL) {
	// 		qrcode(currQRCOdeURL);
	// 		lastQRCodeURL = currQRCOdeURL;
	// 	}
	// }
}

bool WeixinClient::is_login() {
	return m_client->call<bool>("IsLogin");
}

void WeixinClient::subscribe(std::string topic) {
	m_client->subscribe(topic.c_str());
}

void WeixinClient::unsubscribe(std::string topic) {
	m_client->unsubscribe(topic.c_str());
}

std::string WeixinClient::recieve_message(int flag) {
	 char* message = m_client->recieve_message(flag);
	 if (message == nullptr) {
	 	return "";
	 }
	 return std::string(message);
}
