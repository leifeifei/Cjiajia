/*
File name: vector
Author: leifeifei
Date: 2016-3-30
Description: 实现一个向量容器
*/

#include <iostream>
using namespace std;

//定义向量容器
template <class T>
class myvector
{
typedef bool (*sortfunp)(T a,T b);  //申明一个排序谓词函数指针，返回值是bool类型
template <class T1>
friend istream &operator >> (istream& in, myvector<T1>& s);
template <class T1>
friend ostream &operator << (ostream& out, myvector<T1>& s);
public:
   typedef T * my_iterator;         //定义一个输入迭代器
   typedef T * my_const_iterator;   //定义一个只读迭代器

   //以类中类的形式，定义一个反向迭代器
   class reverse_iterator
   {  
    public:
      //初始化反向迭代器
      reverse_iterator()
      {
         rev = NULL; 
      }
      reverse_iterator(T * _ptr)
      {
         rev = _ptr;
      }

      //将后置++重写成后置--，这是实现逆向迭代器最重要的
      reverse_iterator operator ++ (int i)
      {
          reverse_iterator it = *this;
          this->rev = this->rev-1;
          return it.rev;
      }
      bool operator != (reverse_iterator it)
      {
          return this->rev != it.rev;
      }
      T operator * ()
      {
          return *rev;
      }
      reverse_iterator operator - (int i)
      {
         return this->rev-i;
      }
    private:
        T *rev;
   };
   //无参数 - 构造一个空的vector, 
   myvector(T * _ptr=NULL)
   {
      v_size = 0;
      v_capacity = 0;
      ptr = _ptr;
   }

   //数量(num)和值(val) - 构造一个初始放入num个值为val的元素的Vector 
   myvector( int num, const T &val )
   {
   	   resize(num);
   	   int i;
   	   for(i = 0;i < num;i++)
   	   {
   	   	 ptr[i] = val;
   	   }
   }

   //vector(from) - 构造一个与vector from 相同的vector 
   myvector( const myvector &from )
   {
   	 resize(from.v_size);
   	 int i;
   	 for(i = 0;i < from.v_size;i++)
   	 {
   	 	ptr[i] = from.ptr[i];
   	 }
   }

   //迭代器(start)和迭代器(end) - 构造一个初始值为[start,end)区间元素的Vector(注:半开区间). 
   myvector( my_iterator start, my_iterator end )
   {
   	   my_iterator it;
   	   int i = 0;
   	   for(it = start;it != end;it++) //找到start的入口位置
   	   {
            i++;
   	   }
       resize(i);
       i = 0;
       for(it = start;it != end;it++) //将start 到end的元素插入本链表
   	   {
            ptr[i] = *it;
            i++;
   	   }
   }

   ~myvector()
   {
   	  if(ptr != NULL)
   	  {
   	  	delete ptr;
   	  	ptr=NULL;
   	  }
   }
   void resize( int size)
   {
   	  v_size = size;
   	  v_capacity = 2*v_size;
   	  ptr = new T[v_capacity];
   }

   //begin()函数返回一个指向当前vector起始元素的迭代器
   my_iterator begin()
   {
   	   return ptr;
   }

   //end() 函数返回一个指向当前vector末尾元素的下一位置的迭代器.
   my_iterator end()
   {
   	   return ptr+v_size;
   }

   //正序输出
   void output_vector()
   {
  	   my_iterator it;
  	   for( it = begin();it < end();it++ )
  	   {
  		  cout<<*it<<'\t';
  	   }
  	   cout<<endl;
   }

   //返回指向当前vector起始位置的逆迭代器.
    reverse_iterator rend()
    {
      return reverse_iterator(ptr);
    }
    
    //返回指向当前vector末尾的逆迭代器
    reverse_iterator rbegin()
    {
      return reverse_iterator(ptr+v_size);
    }

   //反序输出
   void output_vector_re()
   {
   	   reverse_iterator it;
  	   for(it = rbegin()-1;it != rend();it++)
  	   {
  		  cout<<*it<<'\t';
  	   }
  	   cout<<*it<<endl;
   }

    //at() 函数 返回当前Vector指定位置loc的元素的引用
    T at( int loc )
    {
    	return ptr[loc];
    }

    //back() 函数返回当前vector最末一个元素的引用.
    T back()
    {
    	return *(ptr+v_size-1);
    }

    //push_back()添加值为val的元素到当前vector末尾
    void push_back( const T &val )
    {
      if(ptr == NULL)  //当ptr为空时
      {
        ptr = new T [1];
      }
    	if(this->v_size > this->v_capacity) //判断当前size大小是否超过容量
    	{
    		T *tmp = this->ptr;
    		int len = this->v_size;
    		tmp = new T [len];
    		int j = 0;
    		while(j < len)
    		{
    			tmp[j] = this->ptr[j];
    			j++;
    		}
    		delete this->ptr;
    		this->ptr = NULL;
    		resize(this->v_size);
    		int i = 0;
    		while( i < len)
    		{
    			this->ptr[i] = tmp[i];
    			i++;
    		}
    		delete tmp;
    		tmp = NULL;
    	}
      this->ptr[this->v_size] = val;
      this->v_size = this->v_size+1;      
    }

    //删除当前vector最末的一个元素  
    void pop_back()
    {
    	if(v_size == 0)
    	{
    		return;
    	}
    	v_size--;
    }

    //返回当前vector在重新进行内存分配以前所能容纳的元素数量. 
    int capacity()
    {
    	return v_capacity;
    }

    //函数删除当前vector中的所有元素.
    void clear()
    {
         v_size=0;
    }

    //如果当前vector没有容纳任何元素,则empty()函数返回true,否则返回false
    bool empty()
    {
    	if(this->v_size == 0)
    	{
    		return true;
    	}
    	else
    	{
    		return false;
    	}
    }
    
    //删作指定位置loc的元素,
    my_iterator erase(my_iterator loc)
    {
      int len = this->v_size-1;
      my_iterator it;
      int i = 0;
      for(it = this->begin();it != this->end();it++) //找到loc的后一个位置
      {
        if(it == loc)
        {
          it++;
          break;
        }
        i++;
      }
      while(it != end())  //将loc的位置后的元素往前移动
      {
        this->ptr[i] = *it;
        it++;
        i++;
      }
      this->v_size = len;
    }

    //删除区间[start, end)的所有元素.返回值是指向删除的最后一个元素的下一位置的迭代器
    my_iterator erase( my_iterator start, my_iterator end )
    {
      while(start != end)
      {
        erase(start);
        start++;
      }
    }

    //front()函数返回当前vector起始元素的引用
    T front()
    {
    	return *(this->ptr);
    }
     
     ////在指定位置loc前插入值为val的元素,返回指向这个元素的迭代器,
    my_iterator insert( my_iterator loc, const T &val )
    {
     	int len = this->v_size + 1;
     	if(this->v_size + 1 > this->v_capacity)  //当当前size+1大于当前容量时
    	{
    	   my_iterator it;
    	   it = this->end();
         my_iterator itret = this->begin();
    	   this->resize(len);

         //将当前容量的后面元素，往后移动，若移到loc位置，即插入该元素
    	   while( (it <= itret) && (len != 0) )  
    	   {
    		    if(it == loc)
    		    {
    		       this->ptr[len] = *it;
    		       len--;
    			     this->ptr[len] = val;
    		    }
    		    it--;
    		    len--;
    		    this->ptr[len] = *it;      
    	    }	
    	}
    	else
    	{
    		my_iterator it;
    		it = this->end();

        //将当前容量的后面元素，往后移动，若移到loc位置，即插入该元素
    		while(it != this->begin())
    	  {
    		  if(it == loc)
    		  {
    		    this->ptr[len] = *it;
    		    len--;
    			  this->ptr[len] = val;
    			  break;
    		  }
    		  len--;
    		  it--;
    		  this->ptr[len] = *it;   
    	  }
    	 this->v_size = this->v_size + 1;
    	}	
    	
    }

    //在指定位置loc前插入num个值为val的元素 
    void insert( my_iterator loc, int num, const T &val )
    {
    	while(num--)
    	{
    		insert(loc,val);
    	}
    }

    //在指定位置loc前插入区间[start, end)的所有元素 . 
    void insert( my_iterator loc, my_iterator start, my_iterator end )
    {
    	my_iterator it;
    	while(start != end)
    	{
    		end--;
    		insert(loc,*end);
    	} 	 	
    }
    
    //返回当前vector所容纳元素的数目 
    int size()
    {
    	return this->v_size;
    }
    
    //swap()函数交换当前vector与vector from的元素
    void swap( myvector &from )
    {
    	my_iterator it_from = from.begin();
    	my_iterator it_from_end = from.end();
    	my_iterator it;
    	int len = this->v_size;
      int len_from = from.v_size;
      T *tmp = NULL;
      tmp = new T [len];
      int i = 0;
      for(it = this->begin();it != this->end();it++) //将本向量容器先暂存于tmp
      {
        	tmp[i] = *it;
        	i++;
      }
    	if(from.v_size > this->v_capacity)   //当from的容器size大于它自己本身的容量时
    	{
    		delete this->ptr;
    		ptr = NULL;
    		resize(from.v_size);
    	}
    	i=0;
    	this->v_size = len_from;
    	for(it_from;it_from != it_from_end;it_from++) //将from的容器的元素复制给当前容器
    	{
    		this->ptr[i] = *it_from;
    		i++;
    	} 
      if(len > from.v_capacity)  //当前size大于容量时
    	{
    		delete from.ptr;
    		from.ptr = NULL;
    		resize(len);
    	}
    	from.v_size = len;
    	for(i = 0;i < len;i++)   //将暂存于tmp的当前容器元素，赋给from
    	{
    		from.ptr[i] = tmp[i];
    	}
    } 
    //默认升序
    void sort()
    {
    	int i,j;
    	for(i = 0;i < v_size;i++)
    	{
    		for(j = i;j < v_size;j++)
    		{
    			if(ptr[i] > ptr[j])
    			{
    				T tmp = ptr[i];
    				ptr[i] = ptr[j];
    				ptr[j] = tmp;
    			}
    		}

    	}
    }

    //根据排序位置决定排序方式
    void sort(sortfunp fp)
    {
    	int i,j;
    	for(i = 0;i < v_size;i++)
    	{
    		for(j = i;j < v_size;j++)
    		{
    			if( fp(ptr[i],ptr[j]) )
    			{
    				T tmp = ptr[i];
    				ptr[i] = ptr[j];
    				ptr[j] = tmp;
    			}
    		}
    	}
    }
    
    ////该函数，主要是为了定位 所删除数据，或者插入数据位置而写的，返回所删除或者插入的位置
    my_iterator find(my_iterator begin,my_iterator end,T &val)
    {
    	my_iterator it;
    	for(it = begin;it != end;it++)
    	{
    		if(*it == val)
    		{
    			return it;
    		}
    	}
    } 
 
    //该函数，主要为了重写 == != < > <= >= 符号所写
    int compare(const T * left,const T * right)
    {
    	while(1)
      {
        	if(*left > *right)
        	{
        		return 1;
        	}
        	if(*left < *right)
        	{
        		return -1;
        	}
        	if(*left == *right)
        	{
        		return 0;
        	}
        	left++;
        	right++;
      }  
    }

    //重写下标符号，为了可以像下标一样访问数据
    T & operator[](unsigned index)const
    {
    	return this->ptr[index];
    }
   
    bool operator == (myvector & from)
    {
	     if(compare(this->ptr,from.ptr))
	     {
		     return false;
	     }
	     else
	     {
		     return true;
	     }
	 }

    bool operator != ( myvector & from)
    {
	    if(compare(this->ptr,from.ptr))
	    {
		    return true;
	    }
	    else
	    {
		    return false;
	    }
    }

    bool operator >= ( myvector & from)
    {
	    if(compare(this->ptr,from.ptr) == -1)
	    {
		    return false;
	    }
	    else
	    {
		    return true;
	    }
    }

    bool operator <= ( myvector & from)
    {
	    if(compare(this->ptr,from.ptr) == 1)
	    {
		      return false;
	    }
	    else
	    {
		    return true;
	    }
    }

    bool operator > ( myvector & from)
    {
	    if(compare(this->ptr,from.ptr) == 1)
	    {
		    return true;
	    }
	    else
	    {
		    return false;
	    }
    }

    bool operator < ( myvector & from)
    {
	    if(compare(this->ptr,from.ptr) == -1)
	    {
		    return true;
	    }
	    else
	    {
		    return false;
	    }
    }

private:
	int v_size;      //向量容器当前size大小
	int v_capacity;  //向量容量大小
	T *ptr;
};

//定义一个排序谓词
template <class T>
bool sortdirection (T a,T b)
{
	return a < b;
}

//重写输入符号
template <class T>
istream &operator >> (istream& in,myvector<T>& s)
{
   int i;
   for(i = 0;i < s.v_size;i++)
   {
      in>>s.ptr[i];
   }  
   return in;
}

//重写输出符号
template <class T>
ostream &operator << (ostream& out,myvector<T>& s)
{
   int i;
   for(i = 0;i < s.v_size;i++)
   {
      out<<s.ptr[i]<<'\t';
   }  
   return out;
}

int main(int argc, char const *argv[])
{
	myvector<int> v1;
	v1.push_back(1);
  v1.push_back(7);
  v1.push_back(71);
  v1.push_back(12);
  v1.push_back(12);
  v1.push_back(71);
  v1.push_back(12);
  v1.push_back(12);
  v1.output_vector();
  //v1.output_vector_re();
  //myvector<int>::my_iterator itret=find(v1.begin(),v1.end(),1);
  //v1.erase(itret);
  //v1.erase(v1.begin()+3,v1.end());
    myvector<int> v2(7,66);
    if(v1 == v2)
    {
      cout<<"right"<<endl;
    }
    else
    {
      cout<<"not"<<endl;
    }
    //v2.output_vector();
    //v1.swap(v2);
    //v1.insert(v1.begin()+1,v2.begin()+1,v2.end()-1);
    //v1.insert(v1.begin()+1,55);
    // v1.insert(v1.begin()+1,55);
	//v1.clear();
	//cout<<v1.front()<<endl;
	//v1.output_vector();
	//v2.output_vector(v2);
	//cout<<v1<<endl;
	return 0;
}