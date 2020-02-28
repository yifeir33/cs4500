//
// Created by 王镱霏 on 2/27/20.
//

#ifndef ASSIGNMENT6_MESSAGE_H
#define ASSIGNMENT6_MESSAGE_H

enum class MsgKind { Ack, Nack, Put,

    Reply,  Get, WaitAndGet, Status,

    Kill,   Register,  Directory };


class Message : public Object {

    MsgKind kind_;  // the message kind

    size_t sender_; // the index of the sender node

    size_t target_; // the index of the receiver node

    size_t id_;     // an id t unique within the node


};


#endif //ASSIGNMENT6_MESSAGE_H
