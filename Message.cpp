#include <Message.h>


// RequestMessage的接收函数
void RequestMessage::recv(zmq::socket_t & socket){
    int n=4,i = 0;
    do {
        switch(i){
            case 0: header = s_recv(socket); break;
            case 1: apiName = s_recv(socket); break;
            case 2: reqInfo = s_recv(socket); break;
            case 3: metaData = s_recv(socket); break;
        };
        if( i++ >= n ) break;
    } while(s_more(socket));
    // 消息格式出错检查
    if ( i < n || s_more(socket) ){
        // 执行到这里说明收到的消息和我们定义的帧数不一致
        // TODO: 这里需要抛出异常
    }
}

// RequestMessage的发送函数
void RequestMessage::send(zmq::socket_t & socket){
    // 按Request格式发送消息
    s_sendmore(socket,header);
    s_sendmore(socket,apiName);
    s_sendmore(socket,reqInfo);
    s_send(socket,metaData);
}
