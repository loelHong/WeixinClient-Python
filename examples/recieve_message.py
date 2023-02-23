from wechat import WechatHelper

if __name__ == '__main__':
    helper = WechatHelper("192.168.0.107")
    self_info = helper.wait_until_login()
    print(self_info)

    @helper.message("chat")
    def receive_message(topic, message):
        print(message)

    helper.run_forever(debug=True)
