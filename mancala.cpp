#include <iostream>
using namespace std;

class Mancala {
   private:
      struct Node {
         int data;
         Node* next;
         Node* back;
      };

      Node* _head;
      Node* _tail;

   public:

      /**
       * Creates the initial linked list, assigning each node's value as 1
       * @param nodes: number of nodes to be made in the linked list
       */
      void list_maker (const int nodes) {
         Node* baby = new Node{1, nullptr};
         _head = baby;
         _tail = baby;
         for (int i = 0; i < nodes - 1; i++) {
            Node* baby2 = new Node{1, nullptr};
            Node* temp = _tail;
            _tail->next = baby2;
            _tail = baby2;
            _tail->back = temp;
         }
         _tail->next = _head;
         _head->back = _tail;
      }

      /**
       * Moves one forwards in the linked list while properly assigning the "->back" pointer
       */
      void next_set() {
         Node* temp = _head;
         _head = _head->next;
         _head->back = temp;
      }

      /**
       * Moves one backwards in the linked list while properly assigning the "->next" pointer
       */
      void back_set() {
         Node* temp = _head;
         _head = _head->back;
         _head->next = temp;
      }

      /**
       * Prints the linked list at the end
       * @param nodes: number of nodes to be printed in the linked list
       */
      void print (const int nodes) {
         for (int i = 0; i < nodes - 1; i++) {
            cout << _head->data << " ";
            _head = _head->next;
         }
         cout << _head->data << endl;
      }

      /**
       * Checks to see if the last placed stone should be discarded
       * @param i: follows which number stone is being placed
       * @param num_stones: how any stones total are being placed
       */
      bool discard_check(const int i, const int num_stones) const {
         if (i < num_stones - 1) {
            return true;
         }
         else if (i == num_stones - 1 && _head->data != 0) {
            return true;
         }
         return false;
      }

      /**
       * Places one stone at the specified index in the linked list
       * @param index: determines where the stone should be placed
       * @param nodes: number of nodes in the linked list
       */
      void place(const int index, const int nodes) {
         for (int i = 0; i < nodes; i++) {
            if (i == index) {
               _head->data += 1;
            }
            next_set();
         }
      }

      /**
       * Picks up stones at an index and places them clockwise
       * @param index: determines where the stones should be picked up
       * @param nodes: number of nodes in the linked list
       */
      void clock (const int index, const int nodes) {
         for (int i = 0; i < index; i++) {
            _head = _head->next;
         }
         int num_stones = _head->data;
         _head->data = 0;
         for (int i = 0; i < num_stones; i++) {
            next_set();
            if (discard_check(i, num_stones)) {
               _head->data += 1;
            }
         }
         next_set();
         if (index + num_stones >= nodes) {
            for (int i = nodes; i < index + num_stones + 1; i++) {
               _head = _head->back;
            }
         }
         else if (nodes > index + num_stones) {
            for (int i = index + num_stones; i < nodes - 1; i++) {
               _head = _head->next;
            }
         }
      }

      /**
       * Picks up stones at an index and places them counter-clockwise
       * @param index: determines where the stones should be picked up
       * @param nodes: number of nodes in the linked list
       */
      void anti (const int index, const int nodes) {
         Node* temp = _head;
         for (int i = 0; i < index; i++) {
            _head = _head->next;
         }
         int num_stones = _head->data;
         _head->data = 0;
         for (int i = 0; i < num_stones; i++) {
            back_set();
            if (discard_check(i, num_stones)) {
               _head->data += 1;
            }
         }
         int difference = abs(index - num_stones);
         if (index > num_stones) {
            for (int i = 0; i < difference; i++) {
               _head = _head->back;
            }
         }
         else if (index < num_stones) {
            for (int i = 0; i < difference; i++) {
               _head = _head->next;
            }
         }
      }
};

//Controls operation of the programs
int main() {
   Mancala game;
   string str_nodes, str_moves;
   int nodes, moves;
   cin >> str_nodes >> nodes >> str_moves >> moves;
   game.list_maker(nodes);
   string str_input = "";
   int input = 0;
   for (int counter = 0; counter < moves; counter++) {
      cin >> str_input >> input;
      if (str_input == "place") {
         game.place(input, nodes);
      }
      else if (str_input == "clock") {
         game.clock(input, nodes);
      }
      else if (str_input == "anti") {
         game.anti(input, nodes);
      }
   }
   game.print(nodes);
}
