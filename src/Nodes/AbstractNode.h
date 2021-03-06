//
// Created by Paul Danilin on 04/04/2017.
//

#ifndef FILLWORDSSOLVER_ABSTRACTNODE_H
#define FILLWORDSSOLVER_ABSTRACTNODE_H


class AbstractNode
{
    bool _leaf = false;

protected:
    AbstractNode* _prev;

public:
    virtual void add_edge(wchar_t value, AbstractNode* next) = 0;

    /**
     * Finds the next node with the edge with the char.
     * @param c the char to find out
     * @return a pointer on the next node, nullptr if not found
     */
    virtual AbstractNode* get_next(wchar_t c) = 0;

    void make_leaf()
    { _leaf = true; }

    bool is_leaf() const
    { return _leaf; }

    virtual ~AbstractNode()
    {}

    AbstractNode* get_prev()
    {
        return _prev;
    }
};


#endif //FILLWORDSSOLVER_ABSTRACTNODE_H
