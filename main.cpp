#include <iostream>
#include "FileHandler.h" 
#include "Game.h"

/*Advantages of using linked tables (for commands and instructions):

Dynamic Sizing: In my program, the number of commands and instructions loaded from commands.csv may vary. Using linked lists allows the program to effectively resize based on the actual data read from the file. This dynamic resizing minimizes memory waste and ensures efficient storage.

Disadvantages:

Sequential Access: While linked lists are great for dynamic sizing and efficient insertion/deletion, they require sequential traversal to access elements. In my programs, if I need frequent random access to commands or descriptions (e.g., accessing them by index), linked tables may not be the most efficient choice. Sequential traversal may result in performance degradation when working with large datasets.

Advantages of using arrays (user profiles):

Random access: In the program, user profiles are stored as arrays. This option allows direct random access to profiles using indexes. Arrays provide efficient access when looking up user profiles by name or making changes to them (such as updating scores). This is especially important when working with user profiles, where quick retrieval and modification are common operations.

Disadvantages:

Fixed size: arrays are fixed in size, which means that I need to pre-allocate memory for a specific number of profiles. In my program, if the number of user profiles exceeds the initial size of the array, I may need to perform resizing logic or switch to a more dynamic data structure. This can add complexity to your code.

So, in summary, using linked lists for commands and instructions enables dynamic resizing and is suitable for handling varying amounts of data. However, linked lists are less efficient for random access. On the other hand, arrays work well for user profiles because of their random access capability, but the size of the arrays is fixed and may require additional processing if the number of profiles exceeds the initial allocation.*/

int main() {
    
    FileHandler fileHandler; 
    Game game(fileHandler); 
    game.start();

    return 0;
}
