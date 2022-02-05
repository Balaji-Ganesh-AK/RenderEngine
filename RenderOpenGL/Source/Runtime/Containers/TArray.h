#pragma once
#include <utility>


namespace KREngine
{

	template<typename TArray>
	class TArrayIterator
	{
	public:
		using ValueType = typename TArray::ValueType;
		using PointerType = ValueType*;
		using PointerRef = ValueType&;

		TArrayIterator(PointerType ptr):
			Ptr(ptr)
		{
			
		}

		TArrayIterator& operator++()
		{
			Ptr++;
			return *this;
		}

		TArrayIterator operator++(int)
		{
			TArrayIterator iterator = *this;
			++(*this);
			return iterator;
		}

		TArrayIterator& operator--()
		{
			Ptr--;
			return *this;
		}

		TArrayIterator operator--(int)
		{
			TArrayIterator iterator = *this;
			--(*this);
			return iterator;
		}
		PointerRef operator[](int index)
		{
			return *(Ptr[index]);
		}


		PointerType operator->()
		{
			return Ptr;
		}

		PointerRef operator*()
		{
			return *Ptr;
		}


		bool operator==(const TArrayIterator& other) const
		{
			return Ptr == other.Ptr;
		}

		bool operator!=(const TArrayIterator& other) const
		{
			return !(*this == other);
		}
		

	private:
		PointerType Ptr;
	};


	template <typename ElementType>
	class TArray
	{
	public:
		using ValueType = ElementType;
		using Iterator = TArrayIterator<TArray<ElementType>>;
	public:
		TArray()
		{
			ReAllocate( 2 );
		}
		~TArray()
		{
			Clear();
			::operator delete( Data, Capacity * sizeof( ElementType ) );
		}

		/*Gets the size*/
		size_t GetSize() const
		{
			return Size;
		}
		
		/*Adds the element to the array at the end*/
		void Add(const ElementType& element)
		{
			if(Size >= Capacity)
			{
				ReAllocate( Capacity + Capacity / 2 );
			}

			Data [Size] = element;
			Size++;
		}

		/*Adds the element to the array at the end*/
		void Add( ElementType&& element )
		{
			if ( Size >= Capacity )
			{
				ReAllocate( Capacity + Capacity / 2 );
			}

			new( &Data [Size] ) ElementType( std::move( element ) );
			Size++;
		}

		///*Adds the element to the array at the end*/
		//void Add(const ElementType&& element )
		//{
		//	if ( Size >= Capacity )
		//	{
		//		ReAllocate( Capacity + Capacity / 2 );
		//	}

		//	Data [Size] = std::move( element );
		//	Size++;
		//}


		void RemoveAt( size_t Index )
		{
			Data [Index].~ElementType();
			for ( size_t i = 0; i < Size - 1; i++ )
			{
				if ( i >= Index )
				{
					Data [i] = ( Data [i + 1] );
				}
				
			}
			Size--;
		}
		

		
		/*Adds the element to the array at the end*/
		template<typename... Args>
		void Add( Args&&... args )
		{
			if ( Size >= Capacity )
			{
				ReAllocate( Capacity + Capacity / 2 );
			}

			new( &Data [Size] ) ElementType( std::forward<Args>( args )... );
			Size++;
		}


		
		
		

		/*Adds the element to the array at the end*/
		template<typename... Args>
		ElementType& EmplaceBack( Args&&... args )
		{
			if ( Size >= Capacity )
			{
				ReAllocate( Capacity + Capacity / 2 );
			}

			/*Advance shit da hahaha*/
			/*Ithu same as ithu*/
			/**
			 *std::forward vanthu varadics a unpack panum
			 * Data[Size] = T(std::forward<Args>(args)...);
			 * 
			 */
			new( &Data [Size] ) ElementType( std::forward<Args>( args )... );
			
			/*Increase Size in place and return */
			return Data [Size++];
		}
		
		

		/*Calls the destructor on all the elements and clears the array*/
		void Clear()
		{
			for(size_t i = 0; i < Size; i++)
			{
				Data [i].~ElementType();
			}

			Size = 0;
		}
		
		ElementType& operator[] (size_t Index) 
		{
			/*if(Index >= Size)
			{
				return nullptr;
			}*/
			return Data [Index];
		}

		const ElementType& operator[] ( size_t Index ) const
		{
			/*if ( Index >= Size )
			{
				return nullptr;
			}*/
			return Data [Index];
		}


		ElementType* GetData()
		{
			return Data;
		}
		const ElementType* GetData() const
		{
			return Data;
		}

		/*Iterators*/
		Iterator begin()
		{
			return Iterator(Data);
		}

		Iterator end()
		{
			return Iterator(Data + Size);
		}
	private:

		void ReAllocate(size_t newCapacity)
		{
			/*Allocate the new block with the given size*/
			ElementType* new_data = static_cast<ElementType*>(::operator new(newCapacity * sizeof(ElementType)));

			if(newCapacity < Size )
			{
				Size = newCapacity;
			}
			
			/*Deep copy each bit into the new data*/
			for(size_t i=0; i< Size; i++)
			{
				new( &new_data [i] ) ElementType( std::move( Data [i] ) );
			}

			for ( size_t i = 0; i < Size; i++ )
			{
				Data [i].~ElementType();
			}
			
			/*deletes the data memory*/
			/*same as
			 *
			 * delete [] Data;
			 * but does not call the destructor so we we the below code;
			 */
			::operator delete( Data, Capacity * sizeof( ElementType ) );	
			Data = new_data;
			Capacity = newCapacity;
		}

		
		ElementType* Data = nullptr;

		/*Current active size of the array*/
		size_t Size = 0;

		/*Current max size of the array*/
		size_t Capacity = 0;
	};
}
