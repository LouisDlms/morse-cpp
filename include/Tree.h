class Tree {
    protected:
        unsigned int _tree_length;
        char* _tree;
    public:
        Tree();
        int char_to_path(char& c);
        char path_to_char(int& path);
};