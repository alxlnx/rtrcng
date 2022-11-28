namespace my {
// Sets are usually red-black trees in C++ so I'm making a set here.
using size_type = unsigned int;
class set {
public:
    // Constrcutors and destrcuctors
    set() {}
    ~set() {}

    // Modifying methods:
    void insert();
    void erase();
    // Non-modyfing methods:
    size_type size() const;
    size_type height() const;
    void find() const;
    
private:
    size_type sz{};
        
};
size_type set::size() const 
// Return number of elements in the tree. 
{

}
size_type set::height() const
// Return the height of the tree.
{

}
void set::find() const
{

}
void set::insert()
{

}
void set::erase()
{

}
} // my namespace