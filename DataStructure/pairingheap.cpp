struct Node {
  T v;            // T为权值类型
  Node *ch, *xd;  // ch为该节点儿子的指针，xd为该节点兄弟的指针。
                  // 若该节点没有儿子/兄弟则指针指向空节点 nullptr。
};
Node* merge(Node* a, Node* b) {
  // 若有一个为空则直接返回另一个
  if (a == nullptr) return b;
  if (b == nullptr) return a;
  if (a->v > b->v) swap(a, b);  // swap后a为权值小的堆，b为权值大的堆
  // 将b设为a的儿子
  b->xd = a->ch;
  a->ch = b;
  return a;
}
Node* merges(Node* x) {
  if (x == nullptr || x->xd == nullptr)
    return x;  // 如果该树为空或他没有兄弟（即他的父亲的儿子数小于2），就直接return。
  Node *a = x->xd, *b = a->xd;  // a：x的一个兄弟，b：x的另一个兄弟
  x->xd = a->xd = nullptr;      // 拆散
  return merge(merge(x, a), merges(b));  // 核心部分
}
Node* delete_min(Node* x) { return merges(x->ch); }

struct Node {
  T v;
  Node *ch, *xd;
  Node *fa;  // 新增：fa指针，指向该节点的父亲，若该节点为根节点则指向空节点
             // nullptr
};
Node* merge(Node* a, Node* b) {
  if (a == nullptr) return b;
  if (b == nullptr) return a;
  if (a->v > b->v) swap(a, b);
  a->fa = nullptr;
  b->fa = nullptr;  // 新增：维护fa指针
  b->xd = a->ch;
  if (a->ch != nullptr)  //判断a的子节点是否为空 否则会空指针异常
    a->ch->fa = b;
  a->ch->fa = b;  // 新增：维护fa指针
  a->ch = b;
  return a;
}
Node* merges(Node* x) {
  x->fa = nullptr;  // 新增：维护fa指针
  if (x == nullptr || x->xd == nullptr) return x;
  Node* a = x->xd;
  Node* b = nullptr;
  if (a != nullptr) {
    b = a->xd;
    x->xd = a->xd = nullptr;
  } else {
    x->xd = nullptr;
  }
  a->fa = nullptr;  // 新增：维护fa指针
  return merge(merge(x, a), merges(b));
}
// root为堆的根，x为要操作的节点，v为新的权值，调用时需保证x->v>=v
// 返回值为新的根节点
Node* decrease - key(Node* root, Node* x, LL v) {
  x->v = v;                        // 修改权值
  if (x->fa == nullptr) return x;  // 如果x为根，就不用接下去的步骤了。
  // 把x从fa的子节点中剖出去，这里要分x的位置讨论一下。
  if (x->fa->ch == x)
    x->fa->ch = x->xd;
  else
    x->fa->xd = x->xd;
  x->xd->fa = x->fa;
  x->xd = nullptr;
  x->fa = nullptr;
  return merge(root, x);  // 合并root和x。
}
