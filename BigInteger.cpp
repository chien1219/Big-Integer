#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

class BigInteger{
    public:
      vector<int> myNumber;
      bool neg;
      bool NaN;
    BigInteger()
   {
      myNumber.clear();
      neg = false;
      NaN = false;
   }

   BigInteger(string input)
   {
      if (input.size() == 0)
      {
         myNumber.push_back(0);
         neg = false;
      }
      else
      {
         int start = 0;
         int in_size = input.size();
         if (input.at(0) == '-')
         {
            neg = true;
            start = 1;
         }
         else
            neg = false;

         for (int i = input.size()-1; i>=start; i--)
         {
            myNumber.push_back(input.at(i) - '0');
         }
      }
   }

   ~BigInteger(){}

   BigInteger abs() const
   {
      BigInteger temp;
      temp = (*this);
      temp.neg = false;
      return temp;
   }
    
   bool operator>(const BigInteger &input)
   {
      if (neg == true && input.neg == false)
         return false;
      else if (neg == false && input.neg == true)
         return true;
      else if (neg == true && input.neg == true)
         return !((*this).abs() >= input.abs());   

      if (myNumber.size() > input.myNumber.size())
         return true;
      else if (myNumber.size() < input.myNumber.size())
         return false;

      for (int i = (int)myNumber.size()-1; i >=0; i--)
      {
         if (myNumber.at(i) > input.myNumber.at(i))
            return true;
         else if (myNumber.at(i) < input.myNumber.at(i))
            return false;   
      }
      return false;
   }

    bool operator>=(const BigInteger &input)
   {      
      if (neg == true && input.neg == false)
         return false;
      else if (neg == false && input.neg == true)
         return true;
      else if (neg == true && input.neg == true)
         return !((*this).abs() > input.abs());

      if (myNumber.size() > input.myNumber.size())
         return true;
      else if (myNumber.size() < input.myNumber.size())
         return false;

      for (int i = (int)myNumber.size() - 1; i >=0; i--)
      {
         if (myNumber.at(i) > input.myNumber.at(i))
            return true;
         else if (myNumber.at(i) < input.myNumber.at(i))
            return false;   
      }
      return true;
   }

    bool operator<(const BigInteger& input)
   {
        return !(*this >= input);
    }

    bool operator<=(const BigInteger& input)
   {
        return !(*this > input);
    }
   
   bool operator==(const BigInteger &input)
   {
      if (neg != input.neg)
         return false;

      if (myNumber.size() != input.myNumber.size())
         return false;
      
      for (int i = 0; i < (int)myNumber.size(); i++)
      {
         if (myNumber.at(i) != input.myNumber.at(i))
            return false;
      }
      return true;
   }

    bool operator!=(const BigInteger& input)
   {
        return !(*this == input);
    }

    void operator=(const BigInteger& input)
   {
      neg = input.neg;
      NaN = input.NaN;
      myNumber.clear();
      myNumber.assign(input.myNumber.begin(),input.myNumber.end());
    }

   
    BigInteger operator+(const BigInteger& input)
   {
      BigInteger temp;
      
      // positive plus negative
      if (neg == false && input.neg == true)
      {
         if ((*this).abs() > input.abs())
         {
            temp = (*this).abs() - input.abs();
            temp.neg = false;
            return temp;
         }
         else
         {
            temp = input.abs() - (*this).abs();
            temp.neg = true;
            return temp;         
         }
      }
      // negative plus positive   
      else if (neg == true && input.neg == false)
      {
         if ((*this).abs() > input.abs())
         {
            temp = (*this).abs()- input.abs();
            temp.neg = true;
            return temp;
         }
         else
         {
            temp = input.abs() - (*this).abs();
            temp.neg = false;
            return temp;         
         }
      }
      // negative plus negative
      else if (neg == true && input.neg == true)
      {      
         temp = (*this).abs() + input.abs();
         temp.neg = true;
         return temp;
      }

      // add
      int m_size = ((int)myNumber.size() > (int)input.myNumber.size()) ? (int)myNumber.size() : (int)input.myNumber.size();

      int temp_result = 0;
      int overflow = 0;
      for (int i = 0; i < m_size; i++)
      {
         if (i < (int)myNumber.size() && i <  (int)input.myNumber.size())
            temp_result = myNumber.at(i) + input.myNumber.at(i) + overflow;
         else if (i < (int)myNumber.size())
            temp_result = myNumber.at(i) + overflow;
         else if (i < (int)input.myNumber.size())
            temp_result = input.myNumber.at(i) + overflow;

         if (temp_result>9)
         {
            temp_result -= 10;
            overflow = 1;
            temp.myNumber.push_back(temp_result);
         }
         else
         {
            temp.myNumber.push_back(temp_result);
            overflow = 0;
         }         
      }

      // overflow and push one more 1
      if (overflow == 1)
         temp.myNumber.push_back(1);

      return temp;
    }
   
    BigInteger& operator+=(const BigInteger& input)
   {
      BigInteger temp = input;
      (*this) = (*this) + temp;
      return (*this);
    }

    BigInteger& operator++()
   {
        (*this) += BigInteger("1");
        return *this;
    }

    BigInteger operator++(int)
   {
        BigInteger temp=*this;
        (*this) += BigInteger("1");
        return temp;
    }
   
    BigInteger operator-(const BigInteger& input)
   {
        BigInteger temp;
      
      // positive minus negative
      if (neg == false && input.neg == true)
      {
         temp = (*this).abs() + input.abs();
         temp.neg = false;
         return temp;
      }
      // negative minus positive   
      else if (neg == true && input.neg == false)
      {
         temp = (*this).abs() + input.abs();
         temp.neg = true;
         return temp;
      }
      // negative minus negative   
      else if (neg == true && input.neg == true)
      {   
         if ((*this).abs() > input.abs())
         {
            temp = (*this).abs() - input.abs();
            temp.neg = true;
            return temp;
         }
         else
         {
            temp = input.abs() - (*this).abs();
            temp.neg = false;
            return temp;         
         }
      }
      
      // avoid small number minus big number
      if ((*this).abs() < input.abs())
      {
         temp = input.abs() - (*this).abs();
         temp.neg = true;
         return temp;         
      }

      // minus
      int m_size = ((int)myNumber.size() > (int)input.myNumber.size()) ? (int)myNumber.size() : (int)input.myNumber.size();

      int temp_result = 0;
      int borrow = 0;
      for (int i = 0; i < m_size; i++)
      {
         if (i < (int)myNumber.size() && i <  (int)input.myNumber.size())
            temp_result = myNumber.at(i) - input.myNumber.at(i) + borrow;
         else if (i < (int)myNumber.size())
            temp_result = myNumber.at(i) + borrow;
         else if (i < (int)input.myNumber.size())
            temp_result = input.myNumber.at(i) + borrow;

         if (temp_result<0)
         {
            temp_result += 10;
            borrow = -1;
            temp.myNumber.push_back(temp_result);
         }
         else
         {
            temp.myNumber.push_back(temp_result);
            borrow = 0;
         }         
      }
      
      // remove zero
      if (temp.myNumber.size() != 1)
      {
         int size = (int)temp.myNumber.size();
         for (int i=0; i<size; i++)
         {
            if (temp.myNumber.back() == 0 && temp.myNumber.size()>1)
               temp.myNumber.pop_back();
            else
               break;            
         }
      }

      // avoid -0
      if (temp.myNumber.size() == 1 && temp.myNumber.front() == 0)
         temp.neg = false;

      return temp;
    }
   
   BigInteger& operator-=(const BigInteger& input)
   {
      BigInteger temp = input;
      (*this) = (*this) - temp;
      return (*this);
    }

    BigInteger& operator--()
   {
        (*this) -= BigInteger("1");
        return *this;
    }

    BigInteger operator--(int)
   {
        BigInteger temp = *this;
        (*this) -= BigInteger("1");
        return temp;
    }   
    //start here
   BigInteger operator*(const BigInteger& input)
   {
	   BigInteger temp;
	   BigInteger pan("0");
	   BigInteger duan=input;
	   if((*this)==pan || duan==pan) return pan;
	   else if(neg!=input.neg)
		   temp.neg=true;
	   int c[(int)myNumber.size()*(int)input.myNumber.size()+1];
	   for(int i=0;i<(int)myNumber.size()*(int)input.myNumber.size()+1;i++){
		   c[i]=0;
	   }
	   for (int i=0; i<myNumber.size(); i++){
	           for (int j=0; j<input.myNumber.size(); j++){
	                   c[i+j] += myNumber.at(i) * input.myNumber.at(j);
		   }}
	   for (int k=0; k<input.myNumber.size()*myNumber.size(); k++) 
	      {				     
    	          c[k+1] += c[k]/10;
    	          c[k] =c[k] % 10;
	      }
for (int i=0; i<(int)myNumber.size()*(int)input.myNumber.size()+1; i++) 
   {
        temp.myNumber.push_back(c[i]); 
   }
      return temp;      
   }      
   
   BigInteger& operator*=(const BigInteger& input)
   {
	   BigInteger temp = input;
	   (*this) = (*this) * temp;
	
      return (*this);
    }
   
   BigInteger operator/(const BigInteger& input)
   {
	   BigInteger temp("0");
	   BigInteger temp1 = input;
	if((*this)<input){
	    return temp;  
     }
     else if(temp1==temp){
	     temp.NaN = true;
	     return temp;
     }
	   else{
		   int a=1;
		   BigInteger temp = (*this);
		   while(1){
			temp -= input;
			if(temp < input)break;
			else a++;
		   }   
		   stringstream iss;   iss<<a;   string b;   iss>>b;
		   BigInteger temp2(b);
		   return temp2;
	   }
   }
   
   BigInteger& operator/=(const BigInteger& input)
   { 
	   BigInteger temp = input;
	   (*this) = (*this) / temp;
	   
      return (*this);
    }

   friend ostream& operator<<(ostream& os, const BigInteger& input)
   {
      if (input.NaN)
      {
         os << "NaN";
         return os;
      }

      if (input.myNumber.size() == 1)
      {
         if (input.myNumber.front() != 0 && input.neg)
            os << '-';
	 if(input.myNumber.at(0)==0)
	    os<<"0";
      }
      else if (input.neg)
         os << '-';
      
      int flag=1;
      for (int i = (int)input.myNumber.size() - 1; i >=0; i--){
	      if(input.myNumber.at(i)==0 &&flag ==1);
	      else {
	 os << input.myNumber.at(i);
	 flag=0;
 }
 	}
      return os;
   }
};

int main() {
  string number1, number2;
  while (cin >> number1 >> number2) {
    BigInteger myBigInt1(number1);
    BigInteger myBigInt2(number2);
    BigInteger myBigInt3;
    BigInteger myBigInt4;
    BigInteger myBigInt5;
    BigInteger myBigInt6;
    BigInteger myBigInt7;
    
    cout << (myBigInt1 > myBigInt2) << endl;
    cout << (myBigInt1 < myBigInt2) << endl;
    cout << (myBigInt1 == myBigInt2) << endl;
    cout << (myBigInt1 != myBigInt2) << endl;
   
   myBigInt3 = myBigInt1 + myBigInt2;
   cout << myBigInt3 << endl;
   myBigInt4 = myBigInt1 - myBigInt2;
   cout << myBigInt4 << endl;
   myBigInt5 = myBigInt3 * myBigInt4;
   cout << myBigInt5 << endl;
   
   myBigInt6 = myBigInt1.abs() / myBigInt2.abs();
   cout << myBigInt6 << endl;
   
  }
  return 0;
}
