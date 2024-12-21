#include "s21_array.h"

namespace s21 {

/**
 * @brief Конструктор для инициализации массива из списка инициализации.
 *
 * Этот конструктор выделяет память для массива на основе количества элементов в списке инициализации,
 * копирует элементы из списка в массив и сохраняет размер массива.
 *
 * @param items Список инициализации, содержащий элементы, которые будут скопированы в массив.
 */
template <class value_type, std::size_t Size>
array<value_type, Size>::array(std::initializer_list<value_type> const& items) {
  // Выделяем память для массива размером, соответствующим количеству элементов в списке
  arr = new value_type[items.size()];
  
  // Индекс для копирования значений из списка инициализации в массив
  int i = 0;
  
  // Копируем элементы из списка инициализации в массив
  for (auto it = items.begin(); it != items.end(); it++) {
    arr[i] = *it;  // Присваиваем значение элемента в массив
    i++;  // Увеличиваем индекс
  }
  
  // Устанавливаем размер массива на основе количества элементов в списке
  m_size = items.size();
};


/**
 * @brief Освобождает память, занятую массивом.
 *
 * Этот метод проверяет, был ли выделен массив, и если это так, 
 * освобождает выделенную память с помощью `delete[]`, 
 * затем сбрасывает указатель на массив в `nullptr` и 
 * устанавливает размер массива в 0.
 */
template <class value_type, std::size_t Size>
void array<value_type, Size>::free_array() {
  // Проверяем, был ли массив уже выделен
  if (arr != nullptr) {
    // Освобождаем выделенную память
    delete[] arr;
    // Сбрасываем указатель на массив в nullptr для предотвращения "висячего" указателя
    arr = nullptr;
    // Обнуляем размер массива
    m_size = 0;
  }
}


/**
 * @brief Возвращает ссылку на элемент массива по указанному индексу.
 *
 * Этот метод позволяет получить доступ к элементу массива с проверкой на допустимость индекса.
 * Если индекс выходит за пределы массива, генерируется исключение `std::out_of_range`.
 *
 * @param pos Индекс элемента, к которому нужно получить доступ.
 * @return Ссылка на элемент массива по указанному индексу.
 * @throws std::out_of_range Если индекс выходит за пределы массива.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::reference array<value_type, Size>::at(
    size_type pos) {
  // Проверяем, что индекс не выходит за пределы массива
  if (m_size <= pos) {
    // Если индекс невалиден, генерируем исключение
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }
  
  // Возвращаем ссылку на элемент массива по индексу
  return arr[pos];
}


/**
 * @brief Возвращает ссылку на элемент массива по указанному индексу.
 *
 * Этот метод позволяет получить доступ к элементу массива по индексу.
 * Если индекс выходит за пределы массива, генерируется исключение `std::out_of_range`.
 * В отличие от метода `at()`, который обычно используется для проверки границ,
 * этот оператор предоставляет доступ без явной проверки для быстродействия.
 *
 * @param pos Индекс элемента, к которому нужно получить доступ.
 * @return Ссылка на элемент массива по указанному индексу.
 * @throws std::out_of_range Если индекс выходит за пределы массива.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::reference array<value_type, Size>::operator[](
    size_type pos) {
  // Проверяем, что индекс не выходит за пределы массива
  if (m_size <= pos) {
    // Если индекс невалиден, генерируем исключение
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }

  // Возвращаем ссылку на элемент массива по индексу
  return arr[pos];
}

/**
 * @brief Возвращает ссылку на первый элемент массива.
 *
 * Этот метод возвращает ссылку на первый элемент массива. Если массив пуст (его размер меньше или равен нулю),
 * генерируется исключение `std::out_of_range`.
 *
 * @return Ссылка на первый элемент массива.
 * @throws std::out_of_range Если массив пуст.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_reference
array<value_type, Size>::front() {
  // Проверяем, что массив не пуст
  if (m_size <= 0) {
    // Если массив пуст, генерируем исключение
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }

  // Возвращаем ссылку на первый элемент массива
  return arr[0];
}


/**
 * @brief Возвращает ссылку на последний элемент массива.
 *
 * Этот метод возвращает ссылку на последний элемент массива. Если массив пуст (его размер меньше или равен нулю),
 * генерируется исключение `std::out_of_range`.
 *
 * @return Ссылка на последний элемент массива.
 * @throws std::out_of_range Если массив пуст.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_reference
array<value_type, Size>::back() {
  // Проверяем, что массив не пуст
  if (m_size <= 0) {
    // Если массив пуст, генерируем исключение
    throw std::out_of_range("InvalidIndexError: Index is out of range");
  }

  // Возвращаем ссылку на последний элемент массива
  return arr[m_size - 1];
}


/**
 * @brief Возвращает итератор на начало массива.
 *
 * Этот метод возвращает итератор, который указывает на первый элемент массива.
 *
 * @return Итератор на первый элемент массива.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::iterator array<value_type, Size>::data() {
  return arr;
}

/**
 * @brief Возвращает итератор на начало массива.
 *
 * Этот метод возвращает итератор, который указывает на первый элемент массива. Это основной метод,
 * позволяющий начать итерацию по элементам массива.
 *
 * @return Итератор на первый элемент массива.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::iterator array<value_type, Size>::begin() {
  return iterator(arr);
}

/**
 * @brief Возвращает итератор на элемент, следующий за последним в массиве.
 *
 * Этот метод возвращает итератор, который указывает на элемент за последним в массиве, что важно для завершения
 * итерации и предотвращения выхода за границы массива.
 *
 * @return Итератор на элемент за последним в массиве.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::iterator array<value_type, Size>::end() {
  return iterator(arr + m_size);
}

/**
 * @brief Возвращает константный итератор на начало массива.
 *
 * Этот метод возвращает константный итератор, который указывает на первый элемент массива. Такой итератор
 * позволяет читать элементы, но не изменять их.
 *
 * @return Константный итератор на первый элемент массива.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_iterator
array<value_type, Size>::begin() const {
  return const_iterator(arr);
}

/**
 * @brief Возвращает константный итератор на элемент, следующий за последним в массиве.
 *
 * Этот метод возвращает константный итератор, который указывает на элемент за последним в массиве.
 * Этот итератор необходим для завершения итерации по массиву, при этом элементы нельзя изменять.
 *
 * @return Константный итератор на элемент за последним в массиве.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::const_iterator array<value_type, Size>::end()
    const {
  return const_iterator(arr + m_size);
}

/**
 * @brief Проверяет, пуст ли массив.
 *
 * Этот метод проверяет, пуст ли массив. Если размер массива равен нулю, возвращается `true`, в противном случае `false`.
 *
 * @return `true`, если массив пуст; `false`, если в нем есть элементы.
 */
template <typename T, std::size_t Size>
bool array<T, Size>::empty() {
  return (m_size == 0) ? true : false;
}

/**
 * @brief Возвращает текущий размер массива.
 *
 * Этот метод возвращает количество элементов в массиве.
 *
 * @return Текущий размер массива.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::size_type array<value_type, Size>::size() {
  return m_size;
}


/**
 * @brief Возвращает максимальный размер массива.
 *
 * Этот метод вычисляет максимальный возможный размер массива для данного типа `value_type`. Размер вычисляется
 * с использованием формулы, основанной на размере типа и максимальном значении для индекса в 64-битной системе.
 * В результате получается максимальный индекс, который можно использовать для массивов данного типа.
 *
 * @return Максимальный размер массива, который можно создать для данного типа.
 */
template <class value_type, std::size_t Size>
typename array<value_type, Size>::size_type
array<value_type, Size>::max_size() {
  // Вычисляем максимальный размер массива, основанный на типе value_type
  size_t result = pow(2, (64 - log(sizeof(value_type)) / log(2))) - 1;
  return result;
}


/**
 * @brief Меняет местами содержимое текущего массива и другого массива.
 *
 * Метод `swap` позволяет легко обмениваться содержимым двух массивов типа `array`. Он использует стандартную
 * библиотечную функцию `std::swap` для обмена значениями размеров массивов и указателями на элементы. Это
 * делает обмен содержимым двух массивов эффективным и безопасным.
 *
 * @param other Другой массив, с которым нужно обменяться содержимым.
 */
template <class value_type, std::size_t Size>
void array<value_type, Size>::swap(array& other) {
  // Обмен значений m_size
  std::swap(other.m_size, m_size);
  // Обмен значений arr (указателей)
  std::swap(other.arr, arr);
}

/**
 * @brief Заполняет массив указанным значением.
 *
 * Метод `fill` позволяет заполнить все элементы массива одним и тем же значением. Этот метод полезен для
 * инициализации массива значениями по умолчанию или для обновления всех элементов массива на одно
 * и то же значение, эффективно заменяя содержимое массива.
 *
 * @param value Значение, которым нужно заполнить весь массив.
 */
template <class value_type, std::size_t Size>
void array<value_type, Size>::fill(const_reference value) {
  // Проходим по всем элементам массива и заполняем их указанным значением
  for (size_type i = 0; i < m_size; i++) {
    arr[i] = value;
  }
}


// template class array<int>;
}  // namespace s21
