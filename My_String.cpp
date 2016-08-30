/*
File name:homework1
Author:雷飞飞
UpDate:2016-8-24
Description: 自定义实现string类
*/

#include <iostream>
using namespace std;

class MyString
{
friend ostream& operator << (ostream& out ,MyString & m);
friend istream& operator >> (istream& in,MyString& s);
friend bool operator < ( MyString& left, MyString& right);
friend bool operator > ( MyString& left, MyString& right);
friend bool operator <= ( MyString& left, MyString& right);
friend bool operator >= ( MyString& left, MyString& right);
friend bool operator == ( MyString& left, MyString& right);
friend bool operator != ( MyString& left, MyString& right);
friend MyString operator + ( MyString& left, MyString& right);
public:
typedef char * iterator;
typedef char * input_iterator;
	MyString()
	{
		buf = NULL;
		buf_len = 0; 
	}
    
    //以length为长度的ch的拷贝（即length个ch
	MyString( int length, char ch )
    {
        buf_len = length;
        buf = new char[buf_len + 1];
        int i;
        for (i = 0; i < buf_len; i++)
        {
        	buf[i] = ch;
        }
        buf[i] = '\0';
    }
    
    //以str为初值 (长度任意), 
    MyString( const char *str )
    {
       buf_len = strlen(str);
       buf = new char[buf_len + 1];
       strcpy(buf,str);
    }
    
    MyString( const char *str, int length )
    {
    	buf = new char[length + 1];
    	strncpy(buf,str,length);
    }
    
    //以index为索引开始的子串，长度为length
    MyString( MyString &str, int index, int length )
    {
    	buf_len = length;
    	buf = new char[buf_len + 1];
    	if(index >= str.buf_len)
    	{
    		cout << "index error!!!" << endl;
    		exit(-1);
    	}
        int i,j;
        for(i = index,j = 0; (str.buf[i] != '\0') && (j < buf_len); i++,j++)
        {
        	buf[j] = str.buf[i];
        }
        buf[j]='\0';
    }

    //以start到end的元素为初值，构建对象
    MyString( iterator start, iterator end )
    {
    	int i = 0;
    	iterator it = start;
    	while (it != end)
    	{
    		i++;
    		it++;
    	}
    	buf_len = i;
    	i = 0;
    	buf = new char[buf_len + 1];
    	while (start != end)
    	{
    		buf[i++] = *start++;
    	}
    }

    ~MyString()
	{
		if (buf != NULL)
		{
			delete buf;
			buf = NULL;
		}
	}
    
    //函数返回字符串str 的长度( 即空值结束符之前字符数目
	int strlen(const char *str)
    {
       int ret = 0;
	   while (*str != '\0')
	   {
          ret++;
          str++;
       }
	   return ret;
    }
    
    //复制字符串src 中的字符到字符串dest，包括空值结束符。返回值为指针dest
    char * strcpy(char* dest,const char * src)
    {
    	if(dest == NULL || src == NULL)  //当dest或者src为空时，返回空
    	{
    		return NULL;
    	}  
        int src_len = strlen(src);
        int dest_len = strlen(dest);
        int i = 0;
        if (dest_len < src_len + 1)
        {
            char * tmp = dest;
        	tmp = (char *)tmp + (src_len - dest_len) + 1;
        }
        while (i < src_len)
        {
            dest[i] = src[i++];
        }
        dest[i] = src[i];	
      return dest;
    }
    
    //将字符串src 中至多count个字符复制到字符串dest中。如果字符串src的
    //长度小于count，其余部分用'\0'填补。返回处理完成的字符串
    char * strncpy(char *dest,const char* src,int count)
    {
    	if(src == NULL || dest == NULL)
    	{
    		return NULL; 
    	}
    	int src_len = strlen(src);
    	int dest_len = strlen(dest);
    	char * tmp = dest;
    	int i = 0;
    	if(src_len >= count)  //当src的空间比count大时
    	{
    		if (dest_len < count)
    		{
    			tmp = (char *)tmp + (count - dest_len) + 1;
    		}
    		while (i < count && src[i] != '\0')
    		{
    			dest[i++] = src[i];
    		}    		
    	}
        if (src_len < count)  //当src的空间比count小时
        {
        	if (dest_len < src_len)    //当desc的空间比src小时
        	{
        		tmp = (char *)tmp + (src_len - dest_len) + 1;
        	}
        	while (i < src_len)
        	{
        		dest[i++] = src[i];
        	}
        }
        dest[i] = '\0';
        return dest;
    }

    //函数将字符串str2 连接到str1的末端，并返回指针str1
    char  * strcat(char *str1,const char *str2)
    {
       char * tmp = str1;
	   tmp = (char *)tmp + strlen(str2) + 1;
	   int len = strlen(str1);
	   int i;
	   for (i = 0; str2[i] != '\0'; i++)
	   {
	   	   str1[len + i] = str2[i];
	   } 
	   str1[i] = '\0';
	   return str1;
    } 

    //substr()返回本字符串的一个子串，从index开始，长num个字符。
    //如果没有指定，将是默认值 -1。这样，substr()函数将
    //简单的返回从index开始的剩余的字符串。
    MyString substr( int index, int num = -1 )
    {
        MyString tmp = NULL;
        int i = index;
        int j = 0;
        if(num == -1)
        {
           int len = strlen(buf);
           tmp.buf = new char[len - index + 1];
           while (buf[i] != '\0')
            {
               tmp.buf[j++] = buf[i++];
            }
            tmp.buf[j] = '\0';
            tmp.buf_len = strlen(tmp.buf);
            return tmp;
        }
        else
        {
            tmp.buf = new char[num + 1];
            while( buf[i] != '\0' && j < num)
            {
               tmp.buf[j++] = buf[i++];
            }
            tmp.buf[j] = '\0';
            tmp.buf_len = strlen(tmp.buf);
            return tmp;
        }   
    }

     //比较字符数组大小
    int strcmp(  const char *str, const char *p)
    {
	    while (1)
	    {
		    if (*str > *p) //大于
		    { 
		       return 1;
		    }
			
		    if (*str < *p) //小于
		    {
			   return -1;
		    }

           if (*str == *p)  //等于
           {
        	  if (*str == '\0')
        	  {
                return 0;
        	  }
        	  str++;
        	  p++;
           }
	    }
    }
    
    //和另外一个对象比较, 
    int compare( const MyString &str )
    {
    	if (strcmp( (const char*)buf,str.buf) == 1)    //this > str
    	{
    		return 1;
    	}
        if (strcmp( (const char*)buf,str.buf) == -1)  //this < str
    	{
    		return -1;
    	}
    	if (strcmp( (const char*)buf,str.buf) == 0)   //this == str
    	{
    		return 0;
    	}
    }
    
    //比较自己和str, 
    int compare( const char *str )
    {
    	if (strcmp((const char*)buf,str) == 1)    //this > str
    	{
    		return 1;
    	}
        if (strcmp((const char*)buf,str) == -1)  //this < str
    	{
    		return -1;
    	}
    	if (strcmp((const char*)buf,str) == 0)   //this == str
    	{
    		return 0;
    	}
    }
    
    //比较自己的子串和str,子串以index索引开始，长度为length 
    int compare( int index, int len, const MyString &str )
    {
    	char *tmp = buf;
    	tmp = (char *)tmp + index;
    	if (strcmp( (const char*)tmp,str.buf) == 1)    //this > str
    	{
    		return 1;
    	}
        if (strcmp( (const char*)tmp,str.buf) == -1)  //this < str
    	{
    		return -1;
    	}
    	if (strcmp( (const char*)tmp,str.buf) == 0)   //this == str
    	{
    		return 0;
    	}
    }

     ////比较自己的子串和str的子串，其中index2和len2引用str，index和len1引用自己 
    int compare( int index, int len1, const MyString &str, int index2,int len2 )
    {
        int i = 0;
    	if (len1 <= len2)
        {
            while (i < len1 && buf[index + i] != '\0' && str.buf[index2 + i] != '\0')
            {
                if (buf[index + i] == str.buf[index2 + i] )
                {
                    i++;
                }
                if (buf[index + i] > str.buf[index2 + i])
                {
                    return 1;
                }
                if (buf[index + i] < str.buf[index2 + i])
                {
                    return -1;
                }
            }
            return 0;
        }
        else
        {
            while (i < len2 && buf[index + i] != '\0' && str.buf[index2 + i] != '\0')
            {
                if (buf[index + i] == str.buf[index2 + i] )
                {
                    i++;
                }
                if (buf[index + i] > str.buf[index2 + i])
                {
                    return 1;
                }
                if (buf[index + i] < str.buf[index2 + i])
                {
                    return -1;
                }
            }
            return 0;
        }
    }

    //比较自己的子串和str的子串，其中str的子串以索引0开始，长度为len2，
    //自己的子串以index开始，长度为len1 
    int compare( int index, int len1, const char *str, int len2 )
    {
        int i = 0;
        if (len1 <= len2)
        {
            while (i < len1 && buf[index + i] != '\0' && str[i] != '\0')
            {
                if (buf[index + i] == str[i] )
                {
                    i++;
                }
                if (buf[index + i] > str[i])
                {
                    return 1;
                }
                if (buf[index + i] < str[i])
                {
                    return -1;
                }
            }
            return 0;
        }
        else
        {
            while (i < len2 && buf[index + i] != '\0' && str[i] != '\0')
            {
                if (buf[index + i] == str[i] )
                {
                    i++;
                }
                if (buf[index + i] > str[i])
                {
                    return 1;
                }
                if (buf[index + i] < str[i])
                {
                    return -1;
                }
            }
            return 0;
        }
    }

    MyString &assign( const MyString &str )
    {
        return assign(str.buf);
    }

    //用str为字符串赋值, 
    MyString &assign( const char *str )
    {
        int i = 0;
        if (buf == NULL)
        {
            buf_len = strlen(str);
            buf = new char[buf_len + 1];
            i = 0;
            while (i < buf_len && str[i] != '\0')
            {
                buf[i++] =  str[i];
            }
            buf[i] = '\0';
        }
        else
        {
            strcpy(buf,str);
        }
        return *this;
    }

    //用str的开始num个字符为字符串赋值,
    MyString &assign( const char *str, int num )
    {
        int i = 0;
        if (buf == NULL)
        { 
            buf_len = strlen(str);
            buf = new char[buf_len + 1];
            i = 0;
            while (i < buf_len && str[i] != '\0')
            {
                buf[i++] =  str[i];
            }
            buf[i] = '\0';
        }
        else
        {
            strncpy(buf,str,num);
        }
        return *this;
    }

    //用str的子串为字符串赋值,子串以index索引开始，长度为len 
    MyString &assign( const MyString &str, int index, int len )
    {
        int i = 0;
        if (buf == NULL)
        {
            buf = new char[len + 1];
            buf_len = len;
            i = 0;
            while (i < len && str.buf[index + i] != '\0')
            {
                buf[i++] =  str.buf[index + i];
            }
            buf[i] = '\0';
        }
        else
        {
            char * tmp = new char[len + 1];
            while (i < len && str.buf[index + i] != '\0')
            {
                tmp[i++] = str.buf[index + i];
            }
            tmp[i] = '\0';
            strcpy(buf,tmp);
            delete tmp;
            tmp = NULL;
        }            
        return *this;        
    }

    //用num个字符ch为字符串赋值.
    MyString &assign( int num, char ch )
    {
        int i = 0;
        if (buf == NULL)
        {
            buf = new char[num + 1];
        }
        while (i < num)
        {
            buf[i++] = ch;
        }
        buf[i] = '\0';
        return *this;
    }
    
    //data()函数返回指向自己的第一个字符的指针.
    const char *data()
    {
        return buf;
    }

    iterator begin()
    {
        return buf;
    }

    //length()函数返回字符串的长度. 这个数字应该和
    //size()返回的数字相同.
    int length()
    {
        return strlen(buf); 
    }

    //size()函数返回字符串中现在拥有的字符数
    int size()
    {
        return strlen(buf);
    }
    
    //resize()函数改变本字符串的大小到num, 
    void resize( int num )
    {
        int len = strlen(buf);
        char * tmp = new char[num + 1];
        strcpy(tmp,buf);
        strncpy(buf,tmp,num);
        delete tmp;
        tmp = NULL;
    }

    //新空间的内容不确定。也可以指定用ch填充。
    void resize( int num, char ch )
    {
        int len = strlen(buf);
        char * tmp = new char[num + 1];
        int count = len - num;
        strcpy(tmp,buf);
        strncpy(buf,tmp,num);
        delete tmp;
        tmp = NULL;
        int i = 0;
        if (count > 0)
        { 
            while (count--)
            {
                buf[num + i] = ch;
                i++;
            }
        }
        buf[num + i] = '\0';     
    }

    //max_size()函数返回字符串能保存的最大字符数。
    int max_size()
    {
        int i = 0;
        iterator it = begin();
        while(it != NULL)
        {
           it++;
           i++;
        }
        return (i+1);
    }

    //返回字符ch在字符串中第一次出现的位置（从index开始查找）。
    //如果没找到就返回 0 
    int find( char ch, int index )
    {
        int i;
        for (i = index; i < strlen(buf); i++)
        {
            if (buf[i] == ch)
            {
                return (i + index);
            }
        }
        return -1;
    }
    
    //如果字符串为空则empty()返回真(true)，否则返回假(false).
    bool empty()
    {
        if (buf == NULL);
        {
            return true;
        }
        return false;
    }
    
    //在迭代器i表示的位置前面插入一个字符ch, 
    iterator insert( iterator i, const char &ch )
    {
        iterator it = begin();
        int index = 0;
        while (it != i)
        {
            it++;
            index++;
        }
        
        char * tmp = new char[buf_len + 1];
        strcpy(tmp,buf);
        
        delete buf;
        buf = NULL;
        buf = new char[buf_len + 2];
        int j = 0;
        while (j < index)
        {
            buf[j] = tmp[j++];
        }
        buf[j] = ch;
        while (tmp[j] != '\0')
        {
            buf[j + 1] = tmp[j++];
        }
        delete tmp;
        tmp = NULL;
        buf_len += 1;
        return buf;
    }

    //在字符串的位置index插入字符串str.buf,
    MyString &insert( int index, const MyString &str )
    {
        return insert(index,str.buf);
    }
    
    MyString &insert( int index, const char *str )
    {
        char * tmp = new char[buf_len + 1];
        int i = 0;
        int len = buf_len + strlen(str);
        strcpy(tmp,buf);
        delete buf;
        buf = NULL;
        buf = new char[len + 1];
        i = 0;
        while (i < index)
        {
            buf[i++] = tmp[i]; 
        }
        int j = 0;
        while (str[j] != '\0')
        {
            buf[i++] = str[j++];
        }
        j = index;
        while (i < len && tmp[j] != '\0')
        {
            buf[i++] = tmp[j++];
        }
        delete tmp;
        tmp = NULL;
        buf_len = strlen(buf);
        return *this;
    }
    
    //在字符串的位置index插入字符串str的num个字符, 
    MyString &insert( int index, const char *str, int num )
    {
        iterator it = begin(); 
        int i = 0;
        while (i <= index)
        {
           it++;
           i++;
        }
        i = 0;
        while(i < num)
        {
            insert(it++,str[i++]);
        }
        return *this;        
    }

    //在字符串中查找最后一个与ch不匹配的字符，返回它的位置。
    //搜索从index开始。如果没找到就返回-1
    int find_last_not_of( char ch, int index = 0 )
    {
        if (index == 0)
        {
            return -1;
        }
        int i = index;
        for (; i >=0 ; i--)
        {
            if (buf[i] != ch)
            {
                return i;
                break;
            }
        }
        return -1;
    }
    
    //在字符串中查找最后一个与str中的字符都不匹配的字符，返回它的位置。
    //搜索从index开始，最多查找num个字符如果没找到就返回-1 
    int find_last_not_of( const char *str, int index, int num )
    {
        int i = index;
        int j = 0;
        int len_str = strlen(str);
        int count = index - num + 1;
        if (count > index + 1)
        {
            count = 0;
        }
        if (count < 0)
        {
            count = 0;
        }
        while (j < len_str && i >= count)
        {
            if (str[j] == buf[i])
            {
                j = 0;
                i--;
            }
            j++;
        }
        if (j == len_str)
        {
            return i;
        }
        return -1;
    }

    //在字符串中查找最后一个与ch匹配的字符，返回它的位置。
    //搜索从index开始。如果没找到就返回string::nops 
    int find_last_of( char ch, int index = 0 )
    {
       int i = index;
       int j = 0;
       while (j < buf_len && i >= 0)
       {
          if (buf[i] != ch)
          {
              return i;
              break;
          }
          j++;
       }
       return -1;
    }
    
    //在字符串中查找最后一个与str中的某个字符匹配的字符，返回它的位置。
    //搜索从index开始。如果没找到就返回-1 
    int find_last_of( const MyString &str, int index = 0 )
    {
       return find_last_of(str.buf,index);
    }

    //在字符串中查找最后一个与str中的某个字符匹配的字符，返回它的位置。
    //搜索从index开始。如果没找到就返回-1 
    int find_last_of( const char *str, int index = 0)
    {
       int i = index;
       int j = 0;
       int str_len = strlen(str);
       while (j < str_len && i >= 0)
       {
          if (buf[i] != str[j])
          {
              j = 0;
              i--;
          }
          j++;
       }
       if (j == str_len)
       {
        return i;
       }
       return -1;
    }
    
    //在字符串中查找最后一个与str中的某个字符匹配的字符，返回它的位置。
    //搜索从index开始，最多搜索num个字符。如果没找到就返回string::nops
    int find_last_of( const char *str, int index, int num )
    {
       int i = index;
       int j = 0;
       int str_len = strlen(str);
       int count = index - num + 1;
       if (count > index + 1)
       {
           count = 0;
       }
       if (count < 0)
       {
            count = 0;
       }
       while (j < str_len && i >= count)
       {
          if (buf[i] != str[j])
          {
              j = 0;
              i--;
          }
          j++;
       }
       if (j == str_len)
       {
           return i;
       }
       return -1;
    }

   //swap()函数把str和本字符串交换。
   void swap(MyString &str )
   {
      char * tmp = buf;
      buf = str.buf;
      str.buf = tmp;
      buf_len = strlen(buf);
      str.buf_len = str.strlen(str.buf);
   }

    //用str中的num个字符替换本字符串中的字符,从index开始 
   MyString &replace( int index, int num, const MyString &str )
    {
         return replace(index,num,str.buf);
    }
   
    //用str中的num2个字符（从index2开始）替换本字符串中的字符，从index1开始，最多num1个字符 
    MyString &replace( int index1, int num1, const MyString &str, int index2,int num2 )
    {
         return replace(index1,num1,str.buf,index2,num2);
    }

    //用str中的num个字符（从index开始）替换本字符串中的字符 
    MyString &replace( int index, int num, const char *str )
    {
        int i = index;
        int j = 0;
        while (buf[i] != '\0' && buf[j] != '\0' && num--)
        {
            buf[i++] = str[j++];
        }
        return *this;     
    }

    //用str中的num2个字符（从index2开始）替换本字符串中的字符，从index1开始，num1个字符 
    MyString &replace( int index1, int num1, const char *str,int index2, int num2 )
    {
      int num;
      if (num1 <= num2)
      {
        num = num1;
      }
      if (num1 > num2)
      {
        num = num2;
      }
      int i = index1;
      int j = index2;
      while (buf[i] != '\0' && str[j] != '\0' && num--)
      {
          buf[i++] = str[j++];
      }
      return *this; 
    }

    //用num2个ch字符替换本字符串中的字符，从index开始
    MyString &replace( int index, int num1, int num2, char ch )
    {
      int num;
      if (num1 <= num2)
      {
        num = num1;
      }
      if (num1 > num2)
      {
        num = num2;
      }
      int i = index;
      while (buf[i] != '\0' && num--)
      {
        buf[i++] = ch;
      }
      return *this;
    }

    //删除从index索引开始的num个字符, 返回*this. 
    MyString &erase( int index = 0, int num = 0 )
    {
        int len = strlen(buf);
        int len2 = index + num - 1;
        char * tmp = new char[len - num + 1];
        int i = 0;
        int j = 0;
        while (i < index)
        {
            tmp[i] = buf[i++];
        }
        if (len2 >= len)
        {
            tmp[i] = '\0';
        }
        else
        {
            j = len2 + 1;
            while (j < len )
            {
               tmp[i++] = buf[j++];
            }
            tmp[i] = '\0';
        }
        delete buf;
        buf = NULL;
        buf = tmp;
        buf_len = strlen(buf);
        return *this;
    }

    char & operator [] (unsigned index)const
    {
        return buf[index];
    }
   
    MyString operator = (MyString& right)
    {
       return assign(right);
    }

private:
	char * buf;
	int    buf_len;
};

 bool operator == ( MyString& left, MyString& right)
    {
        if (left.strcmp(left.buf,right.buf) == 0)
        {
            return true;
        }
        return false;
    }

bool operator >= (MyString& left, MyString& right)
{
    if (left.strcmp(left.buf,right.buf) == 0)
    {
        return true;
    }
    if (left.strcmp(left.buf,right.buf) == 1)
    {
        return true;
    }
    return false;
}

bool operator <= ( MyString& left, MyString& right)
{
    if (left.strcmp(left.buf,right.buf) == 0)
    {
        return true;
    }
    if (left.strcmp(left.buf,right.buf) == -1)
    {
        return true;
    }
    return false;
}

bool operator != ( MyString& left, MyString& right)
{
    if (left.strcmp(left.buf,right.buf) == 0)
    {
        return false;
    }
    return true;
}

bool operator > ( MyString& left, MyString& right)
{
    if (left.strcmp(left.buf,right.buf) == 1)
    {
        return true;
    }
    return false;
}

bool operator < ( MyString& left, MyString& right)
{
    if (left.strcmp(left.buf,right.buf) == -1)
    {
        return true;
    }
    return false;
}

MyString operator + ( MyString& left, MyString& right)
{
    int len = left.strlen(left.buf);
    char * tmp = new char[len + 1];
    left.strcpy(tmp,left.buf);
    tmp = left.strcat(tmp,right.buf);
    return tmp;
}

istream &operator >> (istream& in,MyString& s)
{
   int i;
   for(i = 0; i < s.strlen(s.buf); i++)
   {
      in >> s.buf[i];
   }  
   return in;
}

ostream& operator << (ostream& out ,MyString & m)
{
    out << m.buf;
    return out;
}

int main(int argc, char const *argv[])
{
	MyString m1("45454545");
	MyString m2("abcdJ");
	char src[] = "abcdf";
	char dest[] = "8hd";
	//m1.strcat(dest,src);
    //m2.assign(3,'5');

    //m2.insert(2,src,5);
    //int i = m2.find_last_not_of(src,4,3);
    m2.resize(4);
	cout << m2 << endl;
	return 0;
}