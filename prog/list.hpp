#ifndef LIS_H
#define LIS_H

#include <cassert>
#include <iostream>
#include <memory>

class List {
public:
  using Value = int;

  struct Item {
    std::unique_ptr<Item> next;

    Item() : Item(0) {}

    Item(Value v) : value{v} {}

    const Value &get_value() { return value; }

    // ~Item()
    // {
    //   std::cout << "destroying item with value: " << get_value() << std::endl;
    // }

  private:
    Value value;
  };

  /// Erzeugt eine leere Liste
  List()
  {
    // Aufgabe 2
    last = &dummy; // initially list empty; last points to dummy.
  }

  /// Wir loeschen den Copy-Konstruktor. Damit ist es nicht mehr
  /// moeglich aus versehen eine teure Kopie der Liste zu erstellen.
  List(List &) = delete;


  //Aufgabe 1: List Destructor
  ~List()
  {
    while (!empty()) pop_front();
  }

  /// Gibt genau dann `true` zurueck, wenn die Liste leer ist.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// std::cout << lst.empty() << "\n"; // gibt "true" aus.
  /// lst.push_front(1234);
  /// std::cout << lst.empty() << "\n"; // gibt "false" aus.
  /// ```
  bool empty() const { return !dummy.next; }

  /// Gibt die Anzahl der Elemente in der Liste zurueck.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_front(1234);
  /// std::cout << lst.size() << "\n"; // gibt "1" aus.
  /// lst.push_front(1337);
  /// std::cout << lst.size() << "\n"; // gibt "2" aus.
  /// ```
  size_t size() const { return num_items; }

  /// Haengt ein Element mit Wert `val` vorn an die Liste an.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_front(1);
  /// lst.push_front(2);
  /// std::cout << lst << "\n"; // gibt "[2, 1]" aus.
  /// ```
  Item *push_front(Value val) {
    auto new_item = std::make_unique<Item>(val);
    
    // Aufgabe 2:
    // if list empty update last to point to new_item 
    if (empty()) last = new_item.get();

    new_item->next = std::move(dummy.next);
    dummy.next = std::move(new_item);

    ++num_items;
    return dummy.next.get();
  }

  /// Entfernt das erste Element der Liste und gibt das Item als unique_ptr
  /// zurueck. Wenn die Liste leer ist, wird ein "non-owning" smart pointer
  /// zurueckgegeben.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_front(1);
  /// {
  ///    auto item = lst.pop_front();
  ///    assert(item->get_value() == 1);
  /// } // item wird hier freigegeben.
  /// {
  ///    auto item = lst.pop_front();
  ///    assert(!item); // item ist "non-owning" nullptr, da die Liste leer ist.
  /// }
  /// ```
  std::unique_ptr<Item> pop_front() { return extract_after(dummy); }

  /// Hilfsfunktion, die eine Callback-Funktion fuer jedes Element in der Liste
  /// aufruft. Das Callback sollte eine Funktion sein, die ein const Value& als
  /// Argument nimmt.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_front(1);
  /// lst.push_front(2);
  /// lst.foreach([] (const List::Value& val) { std::cout << val << " "; }); //
  /// gibt "2 1 " aus.
  /// ```
  template <typename Callback> void foreach (Callback &&cb) const {
    Item *current = dummy.next.get();
    while (current != nullptr) {
      cb(current->get_value());
      current = current->next.get();
    }
  }

  /// Diese Funktion erlaubt es eine Liste direkt auf einem ostream auszugeben,
  /// z.B. mittels std::cout.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_front(2);
  /// lst.push_front(1);
  /// std::cout << lst << "\n";
  /// ```
  /// Erzeugt die Ausgabe `[1, 2]`
  friend std::ostream &operator<<(std::ostream &stream, const List &list) {
    stream << '[';
    bool first_element = true;
    list.foreach ([&](const Value &value) {
      if (!first_element)
        stream << ", ";
      first_element = false;
      stream << value;
    });
    stream << ']';
    return stream;
  }

  ///////////////////////////////////////////

  /// Haengt ein Element mit Wert `val` hinten an die Liste an.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_back(1);
  /// lst.push_back(2);
  /// std::cout << lst << "\n"; // gibt "[1, 2]" aus.
  /// ```
  Item *push_back(Value val) { //
    return push_back_item(std::make_unique<Item>(val));
  }

  /// Empfaengt ein (owned) unique_ptr<Item> und haengt das Item hinten an die
  /// Liste an.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_back_item(std::make_unique<List::Item>(1));
  /// std::cout << lst << "\n"; // gibt "[1]" aus.
  /// ```
  Item *push_back_item(std::unique_ptr<Item> &&item) {
    assert(!!item); // Tipp: `!!item` ist ein short-cut für
                    // `static_cast<bool>(item)`
    assert(!item->next);

    // Aufgabe 2: 
    last->next = std::move(item);
    last = last->next.get();
    num_items++;
    return last;
  }

  /// Iteriert durch die Liste und ruft `predicate` fuer jedes Element auf.
  /// Wenn `predicate` `true` zurueckgibt, wird das Element an das Ende der
  /// Liste `append_to` verschoben.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// for(int i=0; i<10; ++i) lst.push_back(i);
  /// List lst_even;
  /// lst.move_into_if(lst_even,
  ///   [] (const List::Value& val) { return val % 2 == 0; });
  /// std::cout << lst << std::endl;      // gibt "[1, 3, 5, 7, 9]" aus.
  /// std::cout << lst_even << std::endl; // gibt "[0, 2, 4, 6, 8]" aus.
  /// ```
  template <typename Predicate>
  void move_into_if(List &other, Predicate &&predicate) {
    const size_t initial_size = size() + other.size();
    (void)initial_size; // verhindert eine Warnung, falls assert wegoptimiert
    // wurde

    Item* previous = &dummy;
    Item* current = previous->next.get();
    while (current != nullptr) { 
      if (predicate(current->get_value())) {
        auto extracted = extract_after(*previous);
        current = previous->next.get();
        other.push_back_item(std::move(extracted));
      }
      else {
        previous = previous->next.get();
        current = previous->next.get();
      }
    }
    assert(size() + other.size() == initial_size);
  }

  /// Hängt die übergebene Liste an die aktuelle Liste an; die übergebene Liste
  /// wird dabei geleert.
  ///
  /// # Example
  /// ```c++
  /// List lst1;
  /// lst1.push_back(1);
  /// List lst2;
  /// lst2.push_back(2);
  /// lst1.concat(lst2);
  /// std::cout << lst1 << std::endl; // gibt "[1, 2]" aus.
  /// std::cout << lst2 << std::endl; // gibt "[]" aus.
  /// ```
  void concat(List &other) {
    // (void)other; // verhindert Warnung; kann entfernt werden, sobald die
    // auskommentierte Implementierung genutzt wird.

    last->next = std::move(other.dummy.next);

    // Aufgabe 3 (this was the mistake)
    last = other.last; // comment this line out to get test_concat_twice() to fail

    num_items += other.num_items;
    other.num_items = 0;
    other.last = &other.dummy;
  }

  /// Gibt genau dann `true` zurueck, wenn die Liste sortiert ist.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_back(2);
  /// assert(lst.is_sorted());
  /// lst.push_back(3);
  /// assert(lst.is_sorted());
  /// lst.push_back(1);
  /// assert(!lst.is_sorted());
  /// ```
  bool is_sorted() const {
    if (empty())
      return true;

    Item *current = dummy.next.get();
    while (current->next) {
      if (current->get_value() > current->next->get_value()) {
        return false;
      }
      current = current->next.get();
    }
    return true;
  }

  /// Sortiert die Liste mittels QuickSort-Algorithmus und gibt
  /// die Anzahl der Vergleiche zurück. Als Pivotelement wird immer das erste
  /// Element der Liste verwendet.
  ///
  /// # Example
  /// ```c++
  /// List lst;
  /// lst.push_back(3);
  /// lst.push_back(1);
  /// lst.push_back(2);
  /// lst.push_back(4);
  /// lst.sort();
  /// std::cout << lst << std::endl; // gibt "[1, 2, 3, 4]" aus.
  /// ```
  uint64_t sort()
  {
    uint64_t k = 0;

    if (dummy.next.get() == last) return 0;

    List a;
    List b;
    List c;


    auto pivot_item = pop_front();
    auto pivot_el = pivot_item->get_value();
    b.push_back_item(std::move(pivot_item));


    auto is_less_pivot = [&] (const List::Value& val) {return val < pivot_el;};
    auto is_equal_pivot = [&] (const List::Value& val) {return val == pivot_el;};
    auto is_greater_pivot = [&] (const List::Value& val) {return val > pivot_el;};

    this->move_into_if(a, is_less_pivot);
    k += a.size();
    this->move_into_if(b, is_equal_pivot);
    k += b.size();
    this->move_into_if(c, is_greater_pivot);
    k += c.size();

    if (!a.empty()) k += a.sort();
    if (!c.empty()) k += c.sort();

    if (!a.empty()) this->concat(a);
    if (!b.empty()) this->concat(b);
    if (!c.empty()) this->concat(c);

    return k;
  }

  // traverse list elements and print them out to cout with a
  // while loop
  void traverse() {
    Item* current = dummy.next.get();
    while (current) {
      std::cout << current->get_value() << " ";
      current = current->next.get();
    }
  }

private:
  Item dummy;

  // Aufgabe 2
  Item* last; //points to the last element

  size_t num_items{0};

  std::unique_ptr<Item> extract_after(Item &it) {
    assert(it.next);

    auto popped = std::move(it.next);

    // Aufgabe 2:
    // if to be extracted element is last update last
    if (last == popped.get()) last = &it;
    it.next = std::move(popped->next);

    assert(!popped->next);
    num_items--;

    return popped;
  }
};

#endif // !LIS_H

