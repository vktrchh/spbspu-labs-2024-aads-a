#ifndef QUEUE_HPP
#define QUEUE_HPP

#include <iostream>

namespace belokurskaya
{
  template< class T >
  class Queue
  {
    public:
      Queue()
      {
        capacity_ = initial_capacity_;
        size_ = 0;
        front_ = 0;
        rear_ = -1;
        data_ = new T[capacity_];
      }

      Queue(const Queue& other):
        capacity_(other.capacity_),
        size_(other.size_),
        front_(other.front_),
        rear_(other.rear_),
        data_(nullptr)
      {
        data_ = new T[capacity_];
        try
        {
          std::copy(other.data_, other.data_ + size_, data_);
        }
        catch (const std::exception& e)
        {
          delete[] data_;
          data_ = nullptr;
          throw;
        }
      }

      Queue(Queue&& other) noexcept:
        capacity_(other.capacity_),
        size_(other.size_),
        front_(other.front_),
        rear_(other.rear_),
        data_(other.data_)
      {
        other.data_ = nullptr;
      }

      ~Queue()
      {
        delete[] data_;
      }

      void push(const T & rhs)
      {
        if (isFull())
        {
          addMemory();
        }
        size_++;
        data_[++rear_] = rhs;
      }

      T front()
      {
        if (isEmpty())
        {
          throw std::runtime_error("Queue is empty");
        }
        return data_[front_];
      }

      T pop()
      {
        if (isEmpty())
        {
          throw std::runtime_error("Queue is empty");
        }
        T value = data_[front_];
        Queue temp(*this);
        temp.front_ = (temp.front_ + 1) % capacity_;
        temp.size_--;
        if (temp.size_ == 0)
        {
          temp.front_ = 0;
        }
        swap(temp);
        return value;
      }

      bool isEmpty() const noexcept
      {
        return size_ == 0;
      }

      bool isFull() const noexcept
      {
        return rear_ == capacity_ - 1;
      }

      size_t size() const noexcept
      {
        return size_;
      }

      friend std::ostream& operator<<(std::ostream& out, const Queue< T >& queue)
      {
        for (size_t i = 0; i <= queue.rear_; ++i)
        {
          out << queue.data_[i] << " ";
        }
        return out;
      }

      Queue& operator=(const Queue& other)
      {
        if (this != &other)
        {
          Queue temp(other);
          swap(temp);
        }
        return *this;
      }

      Queue& operator=(Queue&& other)
      {
        if (this != &other)
        {
          delete[] data_;
          capacity_ = other.capacity_;
          size_ = other.size_;
          front_ = other.front_;
          rear_ = other.rear_;
          data_ = other.data_;
          other.capacity_ = initial_capacity_;
          other.size_ = 0;
          other.front_ = 0;
          other.rear_ = -1;
          other.data_ = new T[capacity_];
        }
        return *this;
      }

      void swap(Queue& other) noexcept
      {
        std::swap(data_, other.data_);
        std::swap(capacity_, other.capacity_);
        std::swap(size_, other.size_);
        std::swap(front_, other.front_);
        std::swap(rear_, other.rear_);
      }

    private:
      size_t capacity_;
      size_t size_;
      size_t front_;
      size_t rear_;
      T* data_;

      const size_t initial_capacity_ = 3;
      const size_t capacity_change_factor_ = 2;

      void reallocateMemory(size_t newCapacity)
      {
        if (newCapacity <= capacity_)
        {
          return;
        }
        T* newData = new T[newCapacity];
        try
        {
          size_t elementsToCopy = size();
          size_t j = 0;

          for (size_t i = 0; i < elementsToCopy; ++i)
          {
            newData[j++] = data_[(front_ + i) % capacity_];
          }
          delete[] data_;
          data_ = newData;
          capacity_ = newCapacity;
          front_ = 0;
          rear_ = elementsToCopy - 1;
        }
        catch (const std::exception& e)
        {
          delete[] newData;
          throw;
        }
      }

      void addMemory()
      {
        reallocateMemory(capacity_ * capacity_change_factor_);
      }

      void freeMemory()
      {
        reallocateMemory(capacity_ / capacity_change_factor_);
      }
  };
}

#endif
