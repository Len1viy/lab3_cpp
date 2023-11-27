#ifndef LIST_H
#define LIST_H
#include <iostream>
#include <cassert>
#include <limits>

template <typename T, typename Alloc = std::allocator<T>>
class List;

template<typename T>
struct ListNode {
  union {
    char empty;
    T val;
  };
  ListNode* prev = nullptr;
  ListNode* next = nullptr;
  ~ListNode() {}
};


/*!
 * @brief Класс итератора для списка
 * @tparam T адрусуемый итератором тип
 * @tparam is_const итератор является const_iterator если true,
 *                  обычным iterator в ином случае
 */
template<typename T, bool is_const>
class ListIterator {

  public:

  /*!
   * @brief Тип, обозначающий дистанцию между двумя итераторами,
   *        т.е. результат std::distance(it1, it2)
   */
  typedef ptrdiff_t difference_type;

  /*!
   * @brief Адресуемый итератором тип
   */
  typedef T value_type;

  /*!
   * @brief Тип указателя на хранимое значение,
   *        для const_iterator - const T*, для обычного - T*
   */
  typedef std::conditional_t<is_const, const T, T>* pointer;

  /*!
   * @brief Тип ссылки на хранимое значение,
   *        для const_iterator - const T&, для обычного - T&
   */
  typedef std::conditional_t<is_const, const T, T>& reference;

  /*!
   * @brief Категория итератора
   */
  typedef std::bidirectional_iterator_tag iterator_category;

  /*!
   * @brief Пустой конструктор, разименование созданного итератора приведёт к UB
   * @note Реализует default_initializable из regular
   */
  ListIterator() noexcept;

  /*!
   * @brief Копирующий крнструктор
   * @tparam other_const Константность копируемого иетратора
   * @note Допускает копирование итератора иной константности
   * @note Реализует std::move_constructible и std::copy_constructible
   */
  template<bool other_const>
  ListIterator(const ListIterator<T, other_const>& o) noexcept
      // нельзя из неконстантного в константный
    requires (is_const >= other_const);

  /*!
   * @brief Копирующее перемещение
   * @returns Ссылка на переданный итератор
   * @tparam other_const Константность копируемого иетратора
   * @note Допускает копирование итератора иной константности
   * @note Реализует std::assignable_from<T&, T>, std::copyable и std::swappable
   */
  template<bool other_const>
  ListIterator& operator = (const ListIterator<T, other_const>& o) noexcept
      // нельзя из неконстантного в константный
    requires (is_const >= other_const);

  /*!
   * @brief Разыменование
   * @returns Ссылка на адресуемый элемент списка
   * @note Реализует `{ *i } -> / *can-reference* /` из input_or_output_iterator и indirectly_readable
   */
  reference operator * () const noexcept;

  /*!
   * @brief Обрщение к полям элемента
   * @returns Указатель на адресуемый элемент списка
   */
  pointer operator -> () const noexcept;

  /*!
   * @brief Сравнение итераторов
   * @tparam other_const Константность копируемого иетратора
   * @returns true если итераторы ссылаются на один и тот же элемент,
   *          иначе false
   * @note Реализует equality_comparable из regular
   * @note Опрератор != получаем автоматически
   */
  template<bool other_const>
  bool operator == (const ListIterator<T, other_const>& o) const noexcept;


  /*!
   * @brief Передвигает итератор на следующий элемент списка
   * @returns Ссылка на переданный итератор
   * @note Реализует `{ ++i } -> std::same_as<I&>` из weakly_incrementable
   */
  ListIterator& operator ++ () noexcept;

  /*!
   * @brief Передвигает итератор на следующий элемент списка
   * @returns Состояние итератора до модификации
   * @note Реализует `{ i++ } -> std::same_as<I>` из incrementable
   */
  ListIterator operator ++ (int) noexcept;

  /*!
   * @brief Передвигает итератор на предыдущий элемент списка
   * @returns Ссылка на переданный итератор
   * @note Реализует `{ --i } -> std::same_as<I&>` из bidirectional_iterator
   */
  ListIterator& operator -- () noexcept;

  /*!
   * @brief Передвигает итератор на предыдущий элемент списка
   * @returns Состояние итератора до модификации
   * @note Реализует `{ i-- } -> std::same_as<I>` из bidirectional_iterator
   */
  ListIterator operator -- (int) noexcept;


  private:

  // Тип указателя на узел списка
  typedef std::conditional_t<is_const, const ListNode<T>, ListNode<T>>* node_ptr_t;

  // Узел, на который указывает итератор
  node_ptr_t node;

  // Конструктор в private области,
  // для использования в List
  ListIterator(node_ptr_t node);

  // List может обращаться к privete полям
  template<typename T1, typename Alloc>
  friend class List;

  // Итератор противоположной константности
  // может обращаться к privete полям
  friend ListIterator<T, !is_const>;
};

/*!
 * @brief Двусвязный список
 * @tparam T Тип хранимых значений
 */
template <typename T, typename Alloc>
class List {

  public:

  /*!
   * @brief Тип хранимых значений
   */
  typedef T value_type;

  /*!
   * @brief Ссылка на тип хранимых значений
   */
  typedef T& reference;

  /*!
   * @brief Константная ссылка на тип хранимых значений
   */
  typedef const T& const_reference;

  /*!
   * @brief Тип итератора
   */
  typedef ListIterator<T, false> iterator;

  /*!
   * @brief Тип константного итератора
   */
  typedef ListIterator<T, true> const_iterator;

  /*!
   * @brief Тип, обозначающий дистанцию между двумя итераторами,
   *        т.е. результат std::distance(it1, it2)
   */
  typedef ptrdiff_t difference_type;

  /*!
   * @brief Тип, используемый для преставления размера контейнера
   */
  typedef size_t size_type;

  /*!
   * @brief Тип используемого аллокатора
   */
  typedef Alloc allocator_type;

  /*!
   * @brief Пустой конструктор, создаёт пустой список
   * @param alloc Аллокатор
   */
  List(const allocator_type& alloc = allocator_type())
      noexcept(std::is_nothrow_default_constructible_v<Alloc>);

  /*!
   * @brief Копирующий конструктор
   * @param o Копируемый список
   */
  List(const List& o)
      // Работает только если есть T() и T(a)
    requires std::copy_constructible<T>;

  /*!
   * @brief Копирующий конструктор
   * @param o Копируемый список
   * @param alloc Аллокатор
   */
  List(const List& o, const allocator_type& alloc)
      // Работает только если есть T() и T(a)
    requires std::copy_constructible<T>;

  /*!
   * @brief Перемещающий конструктор
   * @param o Перемещаемый список
   */
  List(List&& o) noexcept;

  /*!
   * @brief Перемещающий конструктор
   * @param alloc Аллокатор
   * @param o Перемещаемый список
   */
  List(List&& o, const allocator_type& alloc);

  /*!
   * @brief Конструктор, заполняющий список n копиями t
   * @param n Количество элементов
   * @param е Значение элемента, которым будет заполнен список
   */
  List(size_type n, const T& t, const allocator_type& alloc = allocator_type())
    requires std::copy_constructible<T>;

  /*!
   * @brief Конструктор, заполняющий список элементами из диапазона [i, j)
   * @param i Начало диапазона для копирования
   * @param j Конец диапазона для копирования
   */
  template<std::input_iterator It>
  List(It i, It j, const allocator_type& alloc = allocator_type())
    requires std::constructible_from<T, std::iter_reference_t<It>>;

  /*!
   * @brief Конструктор, заполняющий список элементами из списка инициализации
   * @param il inisializer_list, из которого будут скопированы значения
   */
  List(std::initializer_list<T> il, const allocator_type& alloc = allocator_type())
    requires std::move_constructible<T>;

  /*!
   * @brief Копирующий оператор присваивания
   * @param o Копируемый список
   */
  List& operator = (const List& o)
      // Работает только если есть T() и T(a)
    requires std::copy_constructible<T>;

  /*!
   * @brief Перемещающий оператор присваивания
   * @param o Перемещаемый список
   */
  List& operator = (List&& o) noexcept;

  /*!
   * @brief Деструктор
   */
  ~List();

  /*!
   * @brief Получения итератора на начало списка
   * @returns Итаратор, адресующий начало списка
   */
  iterator begin() noexcept;

  /*!
   * @brief Получения итератора на конец списка
   * @returns Итаратор, адресующий конец списка
   */
  iterator end() noexcept;

  /*!
   * @brief Получения константного итератора на начало списка
   * @returns Итаратор, адресующий начало списка
   */
  const_iterator begin() const noexcept;

  /*!
   * @brief Получения константного итератора на конец списка
   * @returns Итаратор, адресующий конец списка
   */
  const_iterator end() const noexcept;

  /*!
   * @brief Получения константного итератора на начало списка
   * @returns Итаратор, адресующий начало списка
   */
  const_iterator cbegin() const noexcept;

  /*!
   * @brief Получения константного итератора на конец списка
   * @returns Итаратор, адресующий конец списка
   */
  const_iterator cend() const noexcept;

  /*!
   * @brief Сравнение двух списков
   * @returns true если равны, иначе false
   * @note Также генерирует !=
   */
  bool operator== (const List& o) const;

  /*!
   * @brief Обменивает состояния двух списков между собой
   * @param o Список для обмена состоянием
   */
  void swap(List& o) noexcept;

  /*!
   * @brief Возвращает размер контейнера
   * @returns Размер контейнера
   */
  size_type size() const noexcept;

  /*!
   * @brief Возвращает максимально возможный размер контейнера
   * @returns Максимально возможный размер контейнера
   */
  size_type max_size() const noexcept;

  /*!
   * @brief Проверка списка на пустоту
   * @returns true если список пустой, иначе false
   */
  bool empty() const noexcept;

  /*!
   * @brief Оператор присваивания, заполняющий список элементами
   *        из списка инициализации
   * @param il inisializer_list, из которого будут скопированы значения
   */
  List& operator = (std::initializer_list<T> il)
    requires std::move_constructible<T>;

  /*!
   * @brief Вставка в список элемента, сконструированного
   *        из переданных значений
   * @param p Итератор, перед которым будет вставлен новый элемент
   * @param args Значения для передачи в конструктор элемента
   * @returns Итератор на вставленный элемент
   */
  template<typename ... Args>
  iterator emplace(const_iterator p, Args && ... args)
    requires std::constructible_from<T, Args...>;

  /*!
   * @brief Вставка в список копии переданного значения
   * @param p Итератор, перед которым будет вставлен новый элемент
   * @param t Значения для вставки
   * @returns Итератор на вставленный элемент
   */
  iterator insert(const_iterator p, const T& t)
    requires std::copy_constructible<T>;

  /*!
   * @brief Вставка в список переданного значения при помощи перемещения
   * @param p Итератор, перед которым будет вставлен новый элемент
   * @param t Значения для вставки
   * @returns Итератор на вставленный элемент
   */
  template<typename ... Args>
  iterator insert(const_iterator p, T&& t)
    requires std::move_constructible<T>;

  /*!
   * @brief Вставка в список n копий значения t
   * @param p Итератор, перед которым будут вставлены новые элементы
   * @param n Количество значений для вставки
   * @param t Значения для вставки
   * @returns Итератор на последний вставленный элемент
   */
  iterator insert(const_iterator p, size_type n, const T& t)
    requires std::copy_constructible<T>;

  /*!
   * @brief Вставка в список элементов из диапазона [i, j)
   * @param p Итератор, перед которым будут вставлены новые элементы
   * @param i Начало диапазона
   * @param j Конец диапазона
   * @returns Итератор на последний вставленный элемент
   */
  template<std::input_iterator It>
  iterator insert(const_iterator p, It i, It j)
    requires std::copy_constructible<T>;

  /*!
   * @brief Вставка в список элементов из списка инициализации
   * @param p Итератор, перед которым будут вставлены новые элементы
   * @param il Список инициализации для вставки
   * @returns Итератор на последний вставленный элемент
   */
  iterator insert(const_iterator p,
                  std::initializer_list<T> il)
    requires std::move_constructible<T>;

  /*!
   * @brief Удаление элемента из списка
   * @param q Итератор, адресубщи элемент для удаления
   * @returns Итератор на элемент, находившийся сразу после удаленного
   */
  iterator erase(const_iterator q) noexcept;

  /*!
   * @brief Удаление элементов из списка в диапазоне [q1, q2)
   * @param q1 Начало диапазона
   * @param q2 Конец диапазона
   * @returns Итератор на элемент, находившийся сразу после последнего удаленного
   */
  iterator erase(const_iterator q1, const_iterator q2) noexcept;

  /*!
   * @brief Удаление всех элементов из списка
   */
  void clear() noexcept;

  /*!
   * @brief Замена значений списка на элементы из диапазона [i, j)
   * @param i Начало диапазона
   * @param j Конец диапазона
   */
  template<std::forward_iterator It>
  void assign(It i, It j)
    requires std::copy_constructible<T>;

  /*!
   * @brief Замена значений списка на элементы из списка инициализации
   * @param il Список инициализации для вставки
   */
  void assign(std::initializer_list<T> il)
    requires std::copy_constructible<T>;

  /*!
   * @brief Замена значений списка на n копий значения t
   * @param n Количество значений для вставки
   * @param t Значения для вставки
   */
  void assign(size_type n, const T& t)
    requires std::copy_constructible<T>;

  /*!
   * @brief Получение первого значения в списке
   * @returns Ссылка на первое значение из списка
   */
  reference front();

  /*!
   * @brief Получение первого значения в списке
   * @returns Константная ссылка на первое значение из списка
   */
  const_reference front() const;

  /*!
   * @brief Получение последнего значения в списке
   * @returns Ссылка на последнее значение из списка
   */
  reference back();

  /*!
   * @brief Получение последнего значения в списке
   * @returns Константная ссылка на последнее значение из списка
   */
  const_reference back() const;

  /*!
   * @brief Вставка в начало списка элемента, сконструированного
   *        из переданных значений
   * @param args Значения для передачи в конструктор элемента
   */
  template<typename ... Args>
  void emplace_front(Args ... args)
    requires std::constructible_from<T, Args...>;

  /*!
   * @brief Вставка в конец списка элемента, сконструированного
   *        из переданных значений
   * @param args Значения для передачи в конструктор элемента
   */
  template<typename ... Args>
  void emplace_back(Args ... args)
    requires std::constructible_from<T, Args...>;

  /*!
   * @brief Вставка в начало списка копии переданного значения
   * @param t Значения для вставки
   */
  void push_front(const T& t)
    requires std::copy_constructible<T>;

  /*!
   * @brief Вставка в начало списка переданного значения при помощи перемещения
   * @param t Значения для вставки
   */
  void push_front(T&& t)
    requires std::move_constructible<T>;

  /*!
   * @brief Вставка в конец списка копии переданного значения
   * @param t Значения для вставки
   */
  void push_back(const T& t)
    requires std::copy_constructible<T>;

  /*!
   * @brief Вставка в конец списка переданного значения при помощи перемещения
   * @param t Значения для вставки
   */
  void push_back(T&& t)
    requires std::move_constructible<T>;

  /*!
   * @brief Удаление первого элемента из списка
   */
  void pop_front() noexcept;

  /*!
   * @brief Удаление последнего элемента из списка
   */
  void pop_back() noexcept;

  /*!
   * @brief Получение используемого аллокатора
   * @returns Используемый аллокатор
   */
  allocator_type get_allocator() const noexcept;

  private:

  typedef ListNode<T> node_t;

  typedef std::allocator_traits<Alloc>::template rebind_alloc<node_t> node_allocator_type;

  // -1 -й узел, он же end
  node_t before_begin;

  // Аллокатор для элементов
  allocator_type allocator;

  // Аллокатор для узлов
  node_allocator_type node_allocator;

  // Размер
  size_t list_size = 0;

  template<typename ...Args>
  node_t* allocate(Args ... args);

  void deallocate(node_t* node) noexcept;

  // Соединение двух узлов
  void link(node_t* prev, node_t* next) noexcept;

  // Вставка узла в список
  void insert_node(node_t* prev, node_t* val) noexcept;

  // Удаление узла из списка
  void erase_node(node_t* node) noexcept;

  // Swap без изменения аллокатора
  void swap_state(List& o) noexcept;

};

static_assert(std::bidirectional_iterator<ListIterator<int, false>>);
static_assert(std::bidirectional_iterator<ListIterator<int, true>>);

template<typename T, bool is_const>
ListIterator<T, is_const>::ListIterator() noexcept: node(nullptr) {}

template<typename T, bool is_const>
template<bool other_const>
ListIterator<T, is_const>::ListIterator(const ListIterator<T, other_const>& o) noexcept
    // нельзя из неконстантного в константный
  requires (is_const >= other_const)
    : node(o.node) {}


template<typename T, bool is_const>
template<bool other_const>
ListIterator<T, is_const>& ListIterator<T, is_const>::operator = (const ListIterator<T, other_const>& o) noexcept
    // нельзя из неконстантного в константный
  requires (is_const >= other_const) {
  node = o.node;
  return *this;
}

template<typename T, bool is_const>
ListIterator<T, is_const>::reference ListIterator<T, is_const>::operator * () const noexcept {
  return node->val;
}

template<typename T, bool is_const>
ListIterator<T, is_const>::pointer ListIterator<T, is_const>::operator -> () const noexcept {
  return &node->val;
}

template<typename T, bool is_const>
template<bool other_const>
bool ListIterator<T, is_const>::operator == (const ListIterator<T, other_const>& o) const noexcept{
  return node == o.node;
}


template<typename T, bool is_const>
ListIterator<T, is_const>& ListIterator<T, is_const>::operator ++ () noexcept {
  node = node->next;
  return *this;
}

template<typename T, bool is_const>
ListIterator<T, is_const> ListIterator<T, is_const>::operator ++ (int) noexcept {
  ListIterator res(node);
  node = node->next;
  return res;
}

template<typename T, bool is_const>
ListIterator<T, is_const>& ListIterator<T, is_const>::operator -- () noexcept {
  node = node->prev;
  return *this;
}

template<typename T, bool is_const>
ListIterator<T, is_const> ListIterator<T, is_const>::operator -- (int) noexcept {
  ListIterator res(node);
  node = node->prev;
  return res;
}

template<typename T, bool is_const>
ListIterator<T, is_const>::ListIterator(node_ptr_t node):
    node(node) {}


template <typename T, typename Alloc>
List<T, Alloc>::List(const allocator_type& alloc)
    noexcept(std::is_nothrow_default_constructible_v<Alloc>)
    : before_begin{.empty=0, .prev=&before_begin, .next=&before_begin},
    allocator(alloc), node_allocator(this->allocator)
{}

template <typename T, typename Alloc>
List<T, Alloc>::List(const List& o)
    // Работает только если есть T() и T(a)
  requires std::copy_constructible<T>
    // Сначала инициализируем по умолчанию
    : List(std::allocator_traits<Alloc>::select_on_container_copy_construction(o.allocator))
{
  insert(end(), o.cbegin(), o.cend());
}

template <typename T, typename Alloc>
List<T, Alloc>::List(const List& o, const allocator_type& alloc)
    // Работает только если есть T() и T(a)
  requires std::copy_constructible<T>
    // Сначала инициализируем по умолчанию
    : List(alloc)
{
  insert(end(), o.cbegin(), o.cend());
}

template <typename T, typename Alloc>
List<T, Alloc>::List(List<T, Alloc>&& o) noexcept
    : List(std::move(o.allocator))
{
  swap_state(o);
}

template <typename T, typename Alloc>
List<T, Alloc>::List(List<T, Alloc>&& o, const allocator_type& alloc)
    : List(alloc)
{
  swap_state(o);
}

template <typename T, typename Alloc>
List<T, Alloc>::List(size_type n, const T& t, const allocator_type& alloc)
  requires std::copy_constructible<T>
    :List(alloc)
{
  insert(end(), n, t);
}

template <typename T, typename Alloc>
template<std::input_iterator It>
List<T, Alloc>::List(It i, It j, const allocator_type& alloc)
  requires std::constructible_from<T, std::iter_reference_t<It>>
    :List(alloc)
{
  insert(end(), i, j);
}

template <typename T, typename Alloc>
List<T, Alloc>::List(std::initializer_list<T> il, const allocator_type& alloc)
  requires std::move_constructible<T>
    :List(alloc)
{
  insert(end(), std::move(il));
}

template <typename T, typename Alloc>
List<T, Alloc>& List<T, Alloc>::operator = (const List& o)
    // Работает только если есть T() и T(a)
  requires std::copy_constructible<T>
{
  if (this == &o)
    return *this;
  if constexpr (std::allocator_traits<Alloc>::propagate_on_container_copy_assignment::value) {
    allocator = o.allocator;
  }
  assign(o.cbegin(), o.cend());
  return *this;
}

template <typename T, typename Alloc>
List<T, Alloc>& List<T, Alloc>::operator = (List&& o) noexcept
{
  if constexpr (std::allocator_traits<Alloc>::propagate_on_container_move_assignment::value) {
    allocator = std::move(o.allocator);
  }
  swap_state(o);
  return *this;
}

template <typename T, typename Alloc>
List<T, Alloc>::~List() {
  clear();
}

template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::begin() noexcept {
  return iterator(before_begin.next);
}

template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::end() noexcept {
  return iterator(&before_begin);
}

template <typename T, typename Alloc>
List<T, Alloc>::const_iterator List<T, Alloc>::begin() const noexcept {
  return const_iterator(before_begin.next);
}

template <typename T, typename Alloc>
List<T, Alloc>::const_iterator List<T, Alloc>::end() const noexcept {
  return const_iterator(&before_begin);
}

template <typename T, typename Alloc>
List<T, Alloc>::const_iterator List<T, Alloc>::cbegin() const noexcept {
  return const_iterator(before_begin.next);
}

template <typename T, typename Alloc>
List<T, Alloc>::const_iterator List<T, Alloc>::cend() const noexcept {
  return const_iterator(&before_begin);
}

template <typename T, typename Alloc>
bool List<T, Alloc>::operator== (const List& o) const {
  return list_size == o.list_size &&
         std::equal(begin(), end(), o.begin(), o.end());
}

template <typename T, typename Alloc>
void List<T, Alloc>::swap(List& o) noexcept {

  if constexpr (std::allocator_traits<Alloc>::propagate_on_container_swap::value) {
    std::swap(allocator, o.allocator);
  }
  swap_state(o);
}

template <typename T, typename Alloc>
List<T, Alloc>::size_type List<T, Alloc>::size() const noexcept {
  return list_size;
}

template <typename T, typename Alloc>
List<T, Alloc>::size_type List<T, Alloc>::max_size() const noexcept {
  return std::numeric_limits<size_type>::max();
}

template <typename T, typename Alloc>
bool List<T, Alloc>::empty() const noexcept {
  return list_size == 0;
}

template <typename T, typename Alloc>
List<T, Alloc>& List<T, Alloc>::operator = (std::initializer_list<T> il)
  requires std::move_constructible<T>
{
  assign(std::move(il));
  return *this;
}

template <typename T, typename Alloc>
template<typename ... Args>
List<T, Alloc>::iterator List<T, Alloc>::emplace(const_iterator p, Args && ... args)
  requires std::constructible_from<T, Args...>
{
  node_t *node = allocate(std::forward<Args>(args)...);
  insert_node(p.node->prev, node);
  return iterator(node);
}

template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::insert(const_iterator p, const T& t)
  requires std::copy_constructible<T>
{
  return emplace(p, t);
}

template <typename T, typename Alloc>
template<typename ... Args>
List<T, Alloc>::iterator List<T, Alloc>::insert(const_iterator p, T&& t)
  requires std::move_constructible<T>
{
  return emplace(p, std::move(t));
}

template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::insert(const_iterator p, size_type n, const T& t)
  requires std::copy_constructible<T>
{
  if(n == 0) {
    return iterator(const_cast<node_t*>(p.node));
  }

  iterator prev(p.node->prev);

  try {
    for(size_t i = 0; i < n; ++i) {
      insert(p, t);
    }
  }
  catch(...) {
    erase(++prev, p);
    throw;
  }

  return iterator(p.node->prev);
}

template <typename T, typename Alloc>
template<std::input_iterator It>
List<T, Alloc>::iterator List<T, Alloc>::insert(const_iterator p, It i, It j)
  requires std::copy_constructible<T>
{
  if(i == j) {
    return iterator(const_cast<node_t*>(p.node));
  }

  iterator prev(p.node->prev);

  try {
    for(; i != j; ++i) {
      insert(p, *i);
    }
  }
  catch(...) {
    erase(++prev, p);
    throw;
  }

  return iterator(p.node->prev);
}

template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::insert(const_iterator p,
                                  std::initializer_list<T> il)
  requires std::move_constructible<T>
{
  return insert(p, std::move_iterator(il.begin()),
                std::move_iterator(il.end()));
}

template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::erase(const_iterator q) noexcept
{
  node_t* node = const_cast<node_t*>(q.node);
  iterator next = iterator(node->next);
  erase_node(node);
  deallocate(node);
  return next;
}

template <typename T, typename Alloc>
List<T, Alloc>::iterator List<T, Alloc>::erase(const_iterator q1, const_iterator q2) noexcept
{
  while(q1 != q2) {
    q1 = erase(q1);
  }
  return iterator(const_cast<node_t*>(q2.node));
}

template <typename T, typename Alloc>
void List<T, Alloc>::clear() noexcept {
  erase(begin(), end());
}

template <typename T, typename Alloc>
template<std::forward_iterator It>
void List<T, Alloc>::assign(It i, It j)
  requires std::copy_constructible<T>
{
  if (empty()) {
    insert(end(), i, j);
    return;
  }
  auto first = cbegin();
  auto last = --cend();
  insert(end(), i, j);
  erase(first, ++last);
}

template <typename T, typename Alloc>
void List<T, Alloc>::assign(std::initializer_list<T> il)
  requires std::copy_constructible<T>
{
  if (empty()) {
    insert(end(), std::move(il));
    return;
  }
  auto first = cbegin();
  auto last = --cend();
  insert(end(), std::move(il));
  erase(first, ++last);
}

template <typename T, typename Alloc>
void List<T, Alloc>::assign(size_type n, const T& t)
  requires std::copy_constructible<T>
{
  if (empty()) {
    insert(end(), n, t);
    return;
  }
  auto first = cbegin();
  auto last = --cend();
  insert(end(), n, t);
  erase(first, ++last);
}

template <typename T, typename Alloc>
List<T, Alloc>::reference List<T, Alloc>::front()
{
  return before_begin.next->val;
}

template <typename T, typename Alloc>
List<T, Alloc>::const_reference List<T, Alloc>::front() const
{
  return before_begin.next->val;
}

template <typename T, typename Alloc>
List<T, Alloc>::reference List<T, Alloc>::back()
{
  return before_begin.prev->val;
}

template <typename T, typename Alloc>
List<T, Alloc>::const_reference List<T, Alloc>::back() const
{
  return before_begin.prev->val;
}

template <typename T, typename Alloc>
template<typename ... Args>
void List<T, Alloc>::emplace_front(Args ... args)
  requires std::constructible_from<T, Args...>
{
  emplace(begin(), std::forward<Args>(args)...);
}

template <typename T, typename Alloc>
template<typename ... Args>
void List<T, Alloc>::emplace_back(Args ... args)
  requires std::constructible_from<T, Args...>
{
  emplace(end(), std::forward<Args>(args)...);
}

template <typename T, typename Alloc>
void List<T, Alloc>::push_front(const T& t)
  requires std::copy_constructible<T>
{
  insert(begin(), t);
}

template <typename T, typename Alloc>
void List<T, Alloc>::push_front(T&& t)
  requires std::move_constructible<T>
{
  insert(begin(), std::move(t));
}

template <typename T, typename Alloc>
void List<T, Alloc>::push_back(const T& t)
  requires std::copy_constructible<T>
{
  insert(end(), t);
}

template <typename T, typename Alloc>
void List<T, Alloc>::push_back(T&& t)
  requires std::move_constructible<T>
{
  insert(end(), std::move(t));
}

template <typename T, typename Alloc>
void List<T, Alloc>::pop_front() noexcept {
  erase(begin());
}

template <typename T, typename Alloc>
void List<T, Alloc>::pop_back() noexcept {
  erase(--end());
}

template <typename T, typename Alloc>
template<typename ...Args>
List<T, Alloc>::node_t* List<T, Alloc>::allocate(Args ... args) {
  node_t* node = std::allocator_traits<node_allocator_type>::allocate(node_allocator, 1);
  std::allocator_traits<Alloc>::construct(allocator, &node->val, std::forward<Args>(args)...);
  return node;
}

template <typename T, typename Alloc>
void List<T, Alloc>::deallocate(node_t* node) noexcept {
  std::allocator_traits<Alloc>::destroy(allocator, &node->val);
  std::allocator_traits<node_allocator_type>::deallocate(node_allocator, node, 1);
}

template <typename T, typename Alloc>
void List<T, Alloc>::link(node_t* prev, node_t* next) noexcept {
  prev->next = next;
  next->prev = prev;
}

template <typename T, typename Alloc>
void List<T, Alloc>::insert_node(node_t* prev, node_t* val) noexcept {
  node_t* next = prev->next;
  link(prev, val);
  link(val, next);
  ++list_size;
}

template <typename T, typename Alloc>
void List<T, Alloc>::erase_node(node_t* node) noexcept {
  node_t* prev = node->prev;
  node_t* next = node->next;
  link(prev, next);
  --list_size;
}

template <typename T, typename Alloc>
List<T, Alloc>::allocator_type List<T, Alloc>::get_allocator() const noexcept {
  return allocator;
}

template <typename T, typename Alloc>
void List<T, Alloc>::swap_state(List& o) noexcept {
  node_t *first = before_begin.next;
  node_t *last = before_begin.prev;
  node_t *o_first = o.before_begin.next;
  node_t *o_last = o.before_begin.prev;

  if (o.list_size != 0) {
    link(o_last, &before_begin);
    link(&before_begin, o_first);
  }
  else {
    link(&before_begin, &before_begin);
  }

  if (list_size != 0) {
    link(last, &o.before_begin);
    link(&o.before_begin, first);
  }
  else {
    link(&o.before_begin, &o.before_begin);
  }

  std::swap(list_size, o.list_size);
}

#endif // LIST_H
