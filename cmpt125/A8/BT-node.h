#ifndef _BT_NODE_H_
#define _BT_NODE_H_

struct BTnode {
  public:
    int val; // this is only valid if type == intNode
    struct BTnode * left;
    struct BTnode * right;

};

#endif // _BT_NODE_H_