# 快速开始
前置条件：
* 下载微信服务端程序
* 安装微信3.6.0.18版本


## 安装
```
pip install .
```

## 使用
首先打开cmd命令行，启动微信服务端程序
```
> weixin_server.exe --port1 10086 --port2 10010
```

编写python脚本，与微信服务端通信

```
from wechat import WechatHelper
helper = WechatHelper(127.0.0.1, 10086, 10010)

helper.wait_until_login()

helper.send_text("filehelper", "你好!")

@helper.message("chat")
def receive_message(topic, message):
    print(message)

helper.run_forever()

```


