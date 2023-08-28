#include <iostream>
#include <string>

template<typename T>

class Vector {
private:
    T* m_ptr = nullptr;
    int m_size;
    int m_capacity;

public:
    Vector();
    Vector(int n);
    ~Vector();
    Vector(const Vector& ob);
    Vector(Vector&& ob);
    Vector& operator=(const Vector& ob);
    Vector& operator =(Vector&& ob);
    T& operator[](int index) const;
    T& at(int index) const;
    bool operator >(const Vector& ob);
    bool operator <(const Vector& ob);
    bool operator ==(const Vector& ob);
    T* genElements();
    T getElement(int index);
    void printVector();
    int getSize()const;
    int getCapacity()const;
    void pushBack(const T& elem);
    T popBack();
    bool isEmpty();
    bool isFull();
    void setSize(int s);
    void erase(int index);
    void clear();
    int reserve();
};

template <typename T>
Vector<T>::Vector<T>()
{
    std::cout << "Default " << __func__ << "\n";
    m_size = 0;
    m_capacity = 0;
}

template <typename T>
Vector<T>::Vector<T>(int n)
{
    std::cout << "Parametrized " << __func__ << "\n";
    m_size = n;
    m_capacity = n;
    m_ptr = new T[m_size];
}

template <typename T>
Vector<T>::~Vector()
{
    std::cout << __func__ << "\n";
    delete[] m_ptr;
}

template <typename T>
Vector<T>::Vector<T>(const Vector& ob) :m_size(ob.m_capacity), m_capacity(ob.m_capacity)
{
    std::cout << "Copy " << __func__ << "\n";

    this->m_ptr = new T[m_size];

    for (int i = 0; i < m_size; i++)
    {
        this->m_ptr[i] = ob.m_ptr[i];
    }
}


template <typename T>
Vector<T>::Vector<T>(Vector&& ob) :m_size(ob.m_size), m_capacity(ob.m_capacity)
{
    std::cout << "Move " << __func__ << "\n";

    if (this != &ob)
    {
        this->m_ptr = ob.m_ptr;

        ob.m_ptr = nullptr;
        ob.m_size = 0;
        ob.m_capacity = 0;
    }
}

template <typename T>
Vector<T>& Vector<T>::operator=(const Vector& ob)
{
    std::cout << __func__ << "\n";

    if (this != &ob)
    {
        std::cout << __func__ << "\n";
        this->m_size = ob.m_size;
        this->m_capacity = ob.m_capacity;
        delete[] m_ptr;

        this->m_ptr = new T[this->m_size];

        for (int i = 0; i < m_size; i++)
        {
            this->m_ptr[i] = ob.m_ptr[i];
        }
    }
    return *this;
}


template <typename T>
Vector<T>& Vector<T>::operator =(Vector&& ob)
{
    std::cout << "Move " << __func__ << "\n";

    if (this != &ob)
    {
        delete this->m_ptr;
        this->m_size = ob.m_size;
        this->m_capacity = ob.m_capacity;

        this->m_ptr = ob.m_ptr;

        ob.m_ptr = nullptr;
        ob.m_size = 0;
        ob.m_capacity = 0;
    }
    return *this;
}


template <typename T>
T& Vector<T>::operator[](int index) const
{
    return m_ptr[index];
}

template <typename T>
T& Vector<T>::at(int index) const
{
    if (index < 0 || index >= m_size)
    {
        throw std::out_of_range("Out of range");
    }
    return m_ptr[index];
}


template <typename T>
bool Vector<T>::operator >(const Vector& ob)
{
    bool flag = false;
    if (this->m_size > ob.m_size)
    {
        flag = true;
    }
    std::cout << std::boolalpha << flag << std::endl;
    return flag;
}


template <typename T>
bool Vector<T>::operator <(const Vector& ob)
{
    bool flag = false;
    if (this->m_size < ob.m_size)
    {
        flag = true;
    }
    std::cout << std::boolalpha << flag << std::endl;
    return flag;
}


template <typename T>
bool Vector<T>::operator ==(const Vector& ob)
{
    bool flag = false;
    if (this->m_size == ob.m_size)
    {
        flag = true;
    }
    std::cout << std::boolalpha << flag << std::endl;
    return flag;
}


template <typename T>
T* Vector<T>::genElements()
{
    for (int i = 0; i < m_size; i++)
    {
        m_ptr[i] = rand() % 100 + 1;
    }
    return m_ptr;
}


template <typename T>
T Vector<T>::getElement(int index)
{
    if (index > m_size || m_size < 0)
    {
        std::cout << "Out of range\n";
    }
    else
    {
        std::cout << "Element with value " << m_ptr[index] << " was returned\n";
    }
    return m_ptr[index];
}

template <typename T>
void Vector<T>::printVector()
{
    for (int i = 0; i < m_size; i++)
    {
        std::cout << "element[" << i << "] = " << m_ptr[i] << std::endl;
    }
}


//size, capacity, pushBack, popBack, erase, clear, reserve
template <typename T>
int Vector<T>::getSize()const
{
    return m_size;
}


template <typename T>
void Vector<T>::setSize(int s)
{
    if (m_size < 0)
    {
        std::cout << "Size can't be negative\n";
        throw std::logic_error("Negative size");
    }
    m_size = s;
}

template <typename T>
bool Vector<T>::isEmpty()
{
    if (m_size == 0)
    {
        std::cout << "Vector is empty\n";
        return true;
    }
    else
    {
        return false;
    }
}

template <typename T>
bool Vector<T>::isFull()
{
    if (m_size == m_capacity)
    {
        std::cout << "Vector is full\n";
        return true;
    }
    else
    {
        return false;
    }
}



template <typename T>
void Vector<T>::pushBack(const T& elem)
{
    //bool b = isFull();
    //std::cout << std::boolalpha << b << std::endl;

    if (isFull())
    {
        m_capacity = reserve();
    }

    T* new_ptr = new T[m_capacity];

    for (int i = 0; i < m_capacity; i++)
    {
        new_ptr[i] = m_ptr[i];
    }

    int current_ind = m_size + 1;
    new_ptr[current_ind - 1] = elem;

    m_ptr = new T[m_capacity];

    for (int i = 0; i < m_capacity; i++)
    {
        m_ptr[i] = new_ptr[i];
    }
    m_size = current_ind;

    delete[]new_ptr;
}

template <typename T>
T Vector<T>::popBack()
{
    T elem;
    int current_ind;

    if (m_size > 0)
    {
        elem = m_ptr[m_size - 1];
        this->m_size--;
        current_ind = m_size;
    }
    else
    {
        throw std::logic_error("empty Vector");
    }
    return elem;
}


template <typename T>
int Vector<T>::reserve()
{
    if (m_size >= m_capacity)
    {
        m_capacity = 2 * m_size;
    }
    else
    {
        m_capacity = m_size;
    }
    return m_capacity;
}


template <typename T>
int Vector<T>::getCapacity()const
{
    return m_capacity;
}


template <typename T>
void Vector<T>::erase(int index)
{
    if (index > m_size || index < 0)
    {
        std::cout << "Invalid index\n";
    }
    else if (index == m_size - 1)
    {
        T elem = popBack();
    }
    else
    {
        for (int i = index; i <= m_size; i++)
        {
            m_ptr[i] = m_ptr[i + 1];
        }
        m_size--;
    }
}

template <typename T>
void Vector<T>::clear()
{
    for (int i = 0; i < m_size; i++)
    {
        m_ptr[i] = NULL;
    }
    m_size = 0;
    m_capacity = 0;
}




int main()
{
    int n;
    std::cout << "Enter the number of elements\n";
    std::cin >> n;

    Vector<int> ob(n);
    ob.genElements();
    ob.printVector();
    ob.getElement(2);

    ob[3];
    ob[2] = 45;
    std::cout << "After operator []\n";
    ob.printVector();

    std::cout << "At\n";
    try 
    {
        ob.at(2);
        ob.at(1) = 8;
        ob.at(-3);
    }
    catch (const std::out_of_range& err) 
    {
        std::cout << "Out of range issue, incorrect index" << std::endl;
    }
    ob.printVector();
    

    Vector<int> ob_cp(ob);
    ob > ob_cp;

    Vector<int> ob1;
    ob1 = ob_cp;

    Vector<double> m_ob1(3);
    m_ob1 = std::move(Vector<double>(5));

    Vector<std::string> m_ob2 = std::move(Vector<std::string>(2));

    ob.pushBack(9);
    ob.printVector();
    std::cout << "after pushBack (current size is " << ob.getSize() << ", capacity is " << ob.getCapacity() << ")\n";
    ob.popBack();
    std::cout << "after popBack (current size = " << ob.getSize() << ", capacity is " << ob.getCapacity() << ")\n";
    ob.printVector();

    Vector<int> ob_empty;
    try
    {
        ob_empty.popBack();
    }
    catch (...)
    {
        std::cout << "Vector is empty";
    }

    std::cout << std::endl;

    std::cout << "erase second element\n";
    ob.erase(2);
    ob.printVector();

    return 0;
}