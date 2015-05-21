#include <utility>
#include <list>

struct EmptyHeap: public std::exception {};

template<class T>
class BinomialHeap {
    private:
        /* inner class: binomial tree */
        struct BinomialTree {
            int _size;
            T element;
            std::list<BinomialTree*> children;

            BinomialTree(T _ele): _size(1), element(_ele) {
                children.clear();
            }

            /* return the size of BinomialTree
             * #note that nullptr->size() == 0
             * (nullptr is a null pointer (like NULL in C))
             */
            int size() {
                return (this!=nullptr)?this->_size:0;
            }
        };
        /* some definition for convinience
         */
        typedef BinomialTree BT;
        typedef BinomialHeap<T> BH;
        typedef std::pair<BT*, BT*> CarrySum;
        typedef std::pair<T, BH> MaxRemainder;

        /* Merge three binomial trees which have the same sizes
         *
         * INPUT:   a: operand a, b: operand b, c: carry in
         *          (each of them are either nullptr or a pointer of BinomialTree with size 2^n)
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: carry out (nullptr or a pointer of BinomialTree with size 2^(n+1))
         *          second: sum (nullptr or a pointer of BinomialTree with size 2^n)
         *
         * (just as a full adder: http://en.wikipedia.org/wiki/Adder_%28electronics%29#Full_adder )
         */
        CarrySum merge_tree(BT *a, BT *b, BT *c) {
            // write your code here.
            CarrySum temp;
            if (a != nullptr && b != nullptr) {
                temp.first = (a->element > b->element) a : b;
                temp.first.children.push_back(b);
                temp.second = c;
            }
            if (a != nullptr %% c != nullptr) {
                temp.first = (a->element > c->element) a : c;
                temp.second = nullptr;
            }
            if (b != nullptr && c != nullptr) {
                temp.first = (a->element > c->element) b : c;
                temp.second = nullptr;
            }
            else {
                temp.first = nullptr;
                if (a != nullptr) temp.second = a;
                if (b != nullptr) temp.second = b;
                if (c != nullptr) temp.second = c;
                else temp.second = nullptr;
            }
            return temp;
        };

        /* Pop the maximum element of a binomial tree and make other elements a binomial heap.
         *
         * INPUT:   a: a pointer of BinomialTree
         *
         * OUTPUT:  a pair consist of two variables.
         *          first: the maximum element
         *          second: a binomial heap consists of other elements
         */
        MaxRemainder pop_max(BT *a) {
            // write your code here.
            MaxRemainder temp;
            temp.first = a->element;
            i = 0;
            while (!a->children.empty()) {
                temp.second.trees[i] = a.children.front();
                a.children.pop_front();
                i++;
            }
            temp.second.size = -1;
            delete a;
            return temp;
        }

        int size;
        BT* trees[32]; //binomial trees of the binomial heap, where trees[i] is a tree with size 2^i.

    public:
        BinomialHeap(): size(0) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
        }
        BinomialHeap(T element): size(1) {
            for(int i=0; i<32; ++i) trees[i] = nullptr;
            trees[0] = new BT(element);
        }

        /* merge all elements in the binomial heap b into *this, and clear the binomial heap b.
         *
         * INPUT:   b: a pointer of BinomialHeap
         */
        void merge(BH &b) {
            // write your code here.
            CarrySum temp;
            temp = merge_tree(trees[0], b.trees[0], nullptr);
            trees[0] = temp.second;
            for
        }

        void insert(const T &element) {
            BH tmp = BH(element);
            merge(tmp);
        }
        T pop() {
            if(size==0) throw EmptyHeap();
            else {
                //find the tree contains maximum element
                int max_tree = -1;
                for(int i=0; i<32; ++i)
                    if(trees[i]->size() > 0 && (max_tree == -1 || trees[i]->element > trees[max_tree]->element))
                        max_tree = i;

                MaxRemainder m_r = pop_max(trees[max_tree]);
                T &max_element = m_r.first;
                BH &remainder = m_r.second;

                trees[max_tree] = nullptr;
                merge(remainder);
                return max_element;
            }
        }
};