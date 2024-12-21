#ifndef S21_LIST_H
#define S21_LIST_H

#include <initializer_list>
#include <iostream>

using namespace std;

namespace s21 {
// Определение шаблона класса list, который представляет собой двусвязный список
template <class T>
class list {
 public:
  // Типы, используемые в классе (тип элемента, ссылка на элемент, константная ссылка, размер)
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;

 private:
  // Вложенная структура для представления узла списка
  struct node {
    value_type value_;  // Значение, которое хранится в узле
    node* next_;        // Указатель на следующий узел
    node* prev_;        // Указатель на предыдущий узел
    // Конструктор для инициализации значения узла
    node(const value_type& value)
        : value_(value), next_(nullptr), prev_(nullptr) {}
  };

  size_type size_ = 0;  // Размер списка (количество элементов)
  node* head_ = nullptr;  // Указатель на первый элемент списка
  node* tail_ = nullptr;  // Указатель на последний элемент списка
  node* size_node_ = nullptr;  // Указатель на вспомогательный узел для хранения размера списка

 public:
  // Определение итераторов для обхода списка
  class listIterator {
   private:
    node* ptr_ = nullptr;  // Указатель на текущий узел
    friend class list<value_type>;  // Друзьям класса разрешено доступать к приватным данным

   public:
    listIterator();  // Конструктор по умолчанию
    listIterator(node* ptr);  // Конструктор с указателем на узел
    listIterator& operator++();    // Префиксная операция инкремента (перемещение на следующий элемент)
    listIterator operator++(int);  // Постфиксная операция инкремента
    listIterator& operator--();    // Префиксная операция декремента (перемещение на предыдущий элемент)
    listIterator operator--(int);  // Постфиксная операция декремента
    listIterator operator-(size_type value);  // Операция вычитания для перемещения итератора
    value_type operator*() const;  // Операция разыменования (доступ к значению)
    value_type operator->() const;  // Операция доступа к члену элемента
    bool operator==(listIterator other);  // Операция сравнения итераторов на равенство
    bool operator!=(listIterator other);  // Операция сравнения итераторов на неравенство
  };

  // Константный итератор, который расширяет функциональность обычного итератора, запрещая изменение значений
  class listConstIterator : public listIterator {
   public:
    listConstIterator(listIterator other);  // Конструктор, преобразующий обычный итератор в константный
    const_reference operator*();  // Разыменование в константном итераторе, возвращает константную ссылку
  };

  // Псевдонимы для типов итераторов
  using iterator = listIterator;
  using const_iterator = listConstIterator;

 public:
  // Функции для работы с размером списка
  void set_size_node();  // Устанавливает вспомогательный узел для хранения размера списка
  list();  // Конструктор по умолчанию
  list(size_type n);  // Конструктор с размером
  list(std::initializer_list<value_type> const& items);  // Конструктор для инициализации из списка
  list(const list& l);  // Конструктор копирования
  list(list&& l);  // Конструктор перемещения
  ~list();  // Деструктор

  // Операторы присваивания и другие функции
  list& operator=(list&& l);  // Оператор перемещения
  const_reference front();  // Получение первого элемента
  const_reference back();  // Получение последнего элемента
  iterator begin();  // Получение итератора на первый элемент
  iterator end();  // Получение итератора на элемент после последнего
  bool empty();  // Проверка, пуст ли список
  size_type size();  // Возвращает размер списка
  size_type max_size();  // Максимальный размер списка
  void clear();  // Очистка списка

  // Функции для доступа и модификации элементов
  node* get_at(value_type index);  // Получение узла по индексу
  node* operator[](value_type index);  // Оператор доступа к элементу по индексу
  iterator insert(iterator pos, const_reference value);  // Вставка элемента в заданную позицию
  void erase(iterator pos);  // Удаление элемента по итератору
  void push_back(const_reference value);  // Добавление элемента в конец списка
  void pop_back();  // Удаление последнего элемента
  void push_front(const_reference value);  // Добавление элемента в начало списка
  void pop_front();  // Удаление первого элемента
  void swap(list& other);  // Обмен содержимым двух списков
  void merge(list& other);  // Слияние двух отсортированных списков
  void splice(const_iterator pos, list& other);  // Перемещение элементов другого списка в текущий
  void reverse();  // Реверс списка
  void unique();  // Удаление повторяющихся элементов
  void sort();  // Сортировка списка
  void quick_sort(iterator first, iterator last);  // Быстрая сортировка
  iterator partition(iterator first, iterator last);  // Разделение списка для быстрой сортировки
  node* merge_nodes(node* left_part, node* right_part);  // Слияние двух отсортированных частей
  void delete_size_node();  // Удаление вспомогательного узла для хранения размера списка
};
}  // namespace s21

#include "s21_list.tpp"  // Подключение реализации шаблонных функций

#endif  // S21_LIST_H
