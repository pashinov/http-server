/**
 * File: delegate.hpp
 *
 * Description:
 */

#ifndef delegate_H_
#define delegate_H_

template<typename... Args>
class container
{
public:
    virtual void call(Args...) {} //Вызов функции
    virtual ~container() {}
    container<Args...> *next;//Указатель на следующий элемент
};

template< typename T, typename M, typename... Args >
class mcontainer : public container<Args...>
{
public:
    mcontainer( T* c, M m ) : class_( c ), method_( m ) {}
    void call(Args... args)
    {
        (class_->*method_)( args... );
    }

private:
    T *class_;
    M method_;
};

template< typename M, typename... Args >
class fcontainer : public container<Args...>
{
public:
    fcontainer( M m ) : method_( m ) {}
    void call(Args... args)
    {
        (method_)( args... );
    }

private:
    M method_;
};

template<typename... Args>
class delegate
{
public:
    delegate()
    {
        container_head_ = new container<Args...>(); //Создаем начальный элемент
        container_tail_ = container_head_; //Назначаем конец списка для быстрого добавления новых элементов
        container_head_->next = 0;
    }
    ~delegate()
    {
        //Тут мы полностью удаляем все элементы
        container<Args...> *cont = container_head_;
        while(cont)
        {
            container<Args...> *temp = cont->next;
            delete cont;
            cont = temp;
        }
    }

    //Удаление всех связей
    void clear()
    {
        container<Args...> *cont = container_head_->next;
        while(cont)
        {
            container<Args...> *temp = cont->next;
            delete cont;
            cont = temp;
        }
        container_head_->next = 0;
        container_tail_ = container_head_;
    }

    //Подключение метода
    template<typename T, typename M>
    void Connect(T *c, M m)
    {
        container_tail_->next = new mcontainer< T, M, Args... >(c,m);
        container_tail_->next->next = 0;
        container_tail_ = container_tail_->next;
    }

    //Подключение функции
    template<typename M>
    void Connect(M m)
    {
        container_tail_->next = new fcontainer< M, Args... >(m);
        container_tail_->next->next = 0;
        container_tail_ = container_tail_->next;
    }

    //Отключение метода
    template<typename T, typename M>
    void disconnect(T *c, M m)
    {
        container<Args...> *container = container_head_;
        while(container->next)
        {
            //Тут я использовал dynamic_cast для нахождения нужного элемента.
            //Возможно не лучший спосо, но ничего другого не придумал.
            mcontainer<T, M, Args...> *temp = dynamic_cast< mcontainer<T, M, Args...>* >(container->next);

            if(temp)
            {
                if(container->next == container_tail_)
                {
                    container_tail_ = container;
                }
                container->next = container->next->next;
                delete temp;
                break;
            }
            container = container->next;
        }
    }

    //Отключение функции
    template<typename M>
    void disconnect(M m)
    {
        container<Args...> *container = container_head_;
        while(container->next)
        {
            fcontainer<M, Args...> *temp = dynamic_cast< fcontainer<M, Args...>* >(container->next);

            if(temp)
            {
                if(container->next == container_tail_)
                {
                    container_tail_ = container;
                }
                container->next = container->next->next;
                delete temp;
                break;
            }
            container = container->next;
        }
    }

    //Перегружаем оператор вызова функции
    void operator ()(Args... args)
    {
        call(args...);
    }

    //Ну и сам вызов делегата
    void call(Args... args)
    {
        container<Args...> *container = container_head_;
        while(container)
        {
            container->call(args...);
            container = container->next;
        }
    }
private:
    container<Args...> *container_head_;
    container<Args...> *container_tail_;
};

#endif // delegate_H_
