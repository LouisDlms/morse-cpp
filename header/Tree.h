class Tree {
    public:
        Tree(char value, Tree* _left = nullptr, Tree* _right = nullptr);

    protected:
        char _value;
        Tree* _left;
        Tree* _right;
};