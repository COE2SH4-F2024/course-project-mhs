#ifndef OBJPOS_H
#define OBJPOS_H

// Not really a C++ thing
typedef struct 
{
    int x;
    int y;
} Pos;



class objPos
{
    public:
        Pos* pos;        
        char symbol;

        objPos();  // Default constructor
        objPos(int xPos, int yPos, char sym);  // Parametrized constructor

        objPos(const objPos& other);  // Copy constructor
        objPos& operator=(const objPos& other);  // Copy assignment operator
        objPos(objPos&& other) noexcept;  // Move constructor
        objPos& operator=(objPos&& other) noexcept;  // Move assignment operator
        ~objPos();  // Destructor to delete the dynamically allocated `pos`

        void setObjPos(const objPos& o);  // Set position using another objPos
        void setObjPos(int xPos, int yPos, char sym);  // Set position using x, y, and symbol
       
        objPos getObjPos() const;  // Get a copy of objPos

        char getSymbol() const;  // Get the symbol
        bool isPosEqual(const objPos* refPos) const;  // Check if positions match
        char getSymbolIfPosEqual(const objPos* refPos) const;  // Get symbol if positions match
};

#endif
