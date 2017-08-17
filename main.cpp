#pragma once
#include "stdafx.h"
#include "math.h"
#include <string>
#include <fstream>
#include <io.h>
#include <iostream>
#include <sstream>

using namespace std;

//var
int i;
int j;
int Good_Input_Vector = 0;
int Input_vector[8] = {1,1,1,1,1,1,1,1};
int Input_vector_Value[2] = {4000, 100};
char Value_Range_Target[5][30] = {"Очень большая", "Большая", "Средняя", "Малая", "Очень малая"};
char Value_Visibility[5][30] = {"Нулевая","Малая","Средняя","Большая","Отличная"};
char Value_Height[5][30] = {"Минимальная", "Малая", "Средняя", "Большая", "Максимальная"};
char Value_Weather[5][30] = {"Очень плохие","Плохие","Нормальные","Хорошие","Отличные"};
char Value_Fuel[5][30] = {"Почти нет", "Мало", "Средне", "Достаточно", "Полные баки"};
char Value_Status[5][30] = {"Критическое", "Почти крит.", "Без крит. повр.", "Хорошее", "Очень хорошее"};
char Value_Skill_Pilot[5][30] = {"Очень низкое", "Низкое", "Среднее", "Высокое", "Очень высокое"};
char Value_Wind[5][30] = {"Очень сильный", "Сильный", "Средний", "Слабый", "Почти нет"};

float Vector_Global_Priority[8] = {0.125,0.125,0.125,0.125,0.125,0.125,0.125,0.125};
//int Compare[11][1] = {{1},{1},{3},{3},{5},{5},{7},{7},{9},{9},{9}};
float Compare_Global[8][8] = {{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},
{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1},{1,1,1,1,1,1,1,1}};
float Compare_Terms_Mas[5][5] = {{1,0.33,0.2,0.14,0.11},{3,1,0.5,0.33,0.25},{5,2,1,0.5,0.33},
{7,3,2,1,0.5}, {9,4,3,2,1}};
int Change_BD = 0;
int Change_Input_Vector = 0;
int Good_Alternative; 

char Alternative[8][100] = {"Продолжить полёт", "Сесть на ближайший аэродром", "Возвращаться на базу"};
int Kol_Alternative = 3;
int Buf_Kol_Alternative = 3;
int Value_Alternative[8][8] = {{9,9,5,9,9,9,9,9},{1,3,5,5,9,1,1,1},{1,3,9,1,5,9,5,1}};

float Vector_Local_Priority[8][8];
float Vector_Final_Priority[8];

//functions
float pow(float float_X, float float_Y);

//Work with BD
void Work_Alternative_BD(int New_BD)
{
	int i_file, j_file;
	if ((access("Alternative_BD.txt", 0)) || (New_BD == 1))
	{
    ofstream fwrite;
	remove("Alternative_BD.txt");
	fwrite.open("Alternative_BD.txt");
	fwrite << Kol_Alternative;
	fwrite << '\n';
	for (i_file = 0; i_file < Kol_Alternative; i_file++)
	{
		fwrite << Alternative[i_file];
	fwrite << "  ";
	for (j_file = 0; j_file <= 7; j_file++)
	{
	fwrite << Value_Alternative[i_file][j_file];
	}
	fwrite <<'\n';
	}
	fwrite.close();
	}
	else 
	{

	 FILE * fread = fopen("Alternative_BD.txt", "r");
	 //fread.open("Alternative_BD.txt");
	 char Kol_Alternative_Char[100];
	 char Alternative_Param[10];
	 char Alternative_Buf[120];
	 int Last_Index;
	 Kol_Alternative = atoi(fgets(Kol_Alternative_Char, 100, fread)); 
	 for (i_file = 0; i_file < Kol_Alternative; i_file++)
	 {
	  Last_Index=0;
	  fgets(Alternative_Buf,120,fread);
	  while ((Alternative_Buf[Last_Index + 1] != ' ') || (Alternative_Buf[Last_Index + 2] != ' '))
	  {
		  Last_Index = Last_Index + 1;
	  }
	   strncpy(Alternative[i_file], Alternative_Buf, Last_Index+1);
	   Alternative[i_file][Last_Index+1] = 0; 
	   Last_Index = Last_Index + 3;
	   for (j_file = 0; j_file <= 7; j_file++)
        {
	      Value_Alternative[i_file][j_file] = Alternative_Buf[Last_Index] - '0';
	      Last_Index = Last_Index + 1;
	    }
	   /*
	  fgets(Alternative[i_file], 100, fread);
	  
//	  char test_buf[100];
//	  strcpy(test_buf, Alternative[i_file]);
	  fgets(Alternative_Param, 10, fread);
	  
	  for (j_file = 0; j_file <= 7; j_file++)
      {
	   Value_Alternative[i_file][j_file] = Alternative_Param[j_file] - '0';
	  }
	  */
	 }
	 fclose(fread); 
	}
}


//COMPARE_FUNCTION
//RANGE
int Compare_Range (int Range_target)
{
		  if (Range_target>=3400) 
		  {
			 return 1;
		  }
		  else if ((Range_target<3400) && (Range_target>=2100))
		  {
			 return 3;
		  }
		  else if ((Range_target<2100) && (Range_target>=1800))
		  {
		     return 5;
		  }
		  else if ((Range_target<1800) && (Range_target>=800))
		  {
			 return 7;
		  }
		  else if ((Range_target<800))
		  {
			 return 9;
		  }
}
//HEIGHT
int Compare_Height (int Height)
{
	if (Height<4000) 
		  {
			 return 1;
		  }
		  else if ((Height>=4000) && (Height<8000))
		  {
			 return 3;
		  }
		  else if ((Height>=8000) && (Height<12000))
		  {
			  return 5;
		  }
		  else if ((Height>=12000) && (Height<16000))
		  {
			  return 7;
		  }
		  else if ((Height>=16000))
		  {
			  return 9;
		  }
}


//Compare 2 terms
/*float Compare_Terms(int term1, int term2)
{
	int term1_mas, term2_mas;
	term1_mas = term1/2;
	term2_mas = term2/2;
	return Compare_Terms_Mas[term1_mas][term2_mas];
}
*/

//MATRIX_GLOBAL_COMPARE
void Matrix_Global_Compare(int (&Input_vec)[8])
{
  for (i=0; i<=7; i++)
  {
	for (j=0; j<=7; j++)
	{
	  Compare_Global[i][j] = Compare_Terms_Mas[Input_vec[i]/2][Input_vec[j]/2];
	}
  }
}


//CALCULATE_GLOBAL_VECTOR_PRIORITY
void Calculate_Global_Priority(float (&Compare_Global)[8][8])
{ 
  double w[8]={1,1,1,1,1,1,1,1};
  float sum_w=0;
  for (i=0; i<=7; i++)
  {
   for (j=0; j<=7; j++)
   {
	 w[i]=w[i]*Compare_Global[i][j];
   }
     w[i] = pow(w[i], 0.125);
     sum_w=sum_w+w[i];
  }
  for (i=0; i<=7; i++)
  {
	Vector_Global_Priority[i] = w[i]/sum_w;
  }
}

//CALCULATE_LOCAL_VECTOR_PRIORITY
void Calculate_Vector_Local_Priority(float (&Compare_Local)[8][8], int Nomer, int Kol_Alternative)
{ 
  float w[8]={1,1,1,1,1,1,1,1};
  int h,g;
  float sum_w=0;
  float Invers_Kol_Alternative;
  double test = Kol_Alternative;
  Invers_Kol_Alternative = 1 / test;
  for (h=0; h<Kol_Alternative; h++)
  {
   for (g=0; g<Kol_Alternative; g++)
   {
	 w[h]=w[h]*Compare_Local[h][g];
   }
     w[h] = pow(w[h], Invers_Kol_Alternative);
     sum_w=sum_w+w[h];
  }
  for (h=0; h<Kol_Alternative; h++)
  {
	Vector_Local_Priority[h][Nomer] = w[h]/sum_w;
  }
}

//CALCULATE_LOCAL_VECTOR_PRIORITY
void Calculate_Local_Priority()
{
	int Change_Alternative[8];
	int k;
	float Compare_Local[8][8];
	int Max = 0; 
	int Min = 10;
	int i_change_a;
	int Criterion = Input_vector[i];

	for (i_change_a = 0; i_change_a < Kol_Alternative; i_change_a++)
	{
	 Change_Alternative[i_change_a] = Value_Alternative[i_change_a][i];
	}

	for (j=0; j<Kol_Alternative; j++)
	{
	  if (Change_Alternative[j] <= Criterion)
	  {
		 Change_Alternative[j] = Criterion - (Change_Alternative[j]-1);
	  }
	  else 
	  {
		  Change_Alternative[j] = Change_Alternative[j] - (Criterion-1);
	  }
	  if (Change_Alternative[j] > Max)
	  {
		  Max = Change_Alternative[j];
	  }
	  if (Change_Alternative[j] < Min)
	  {
		  Min =  Change_Alternative[j];
	  }
	}

	for (j=0; j<Kol_Alternative; j++)
	{
		if (Change_Alternative[j] == Max)
		{
			Change_Alternative[j] = Min;
		}
		else if (Change_Alternative[j] == Min)
		{
			Change_Alternative[j] = Max;
		}
	}
    for (j=0; j<Kol_Alternative; j++)
	{
	 for (k=0; k<Kol_Alternative; k++)
	 {
	   Compare_Local[j][k] = Compare_Terms_Mas[Change_Alternative[j]/2][Change_Alternative[k]/2];
	   //Compare_Local[j][k] = Compare_Terms(Change_Alternative[j], Change_Alternative[k]);
	 }
	}
	
  float w[8]={1,1,1,1,1,1,1,1};
  int h,g;
  float sum_w=0;
  float Invers_Kol_Alternative;
  double test = Kol_Alternative;
  Invers_Kol_Alternative = 1 / test;
  for (h=0; h<Kol_Alternative; h++)
  {
   for (g=0; g<Kol_Alternative; g++)
   {
	 w[h]=w[h]*Compare_Local[h][g];
   }
     w[h] = pow(w[h], Invers_Kol_Alternative);
     sum_w=sum_w+w[h];
  }
  for (h=0; h<Kol_Alternative; h++)
  {
	Vector_Local_Priority[h][i] = w[h]/sum_w;
  }

	//Calculate_Vector_Local_Priority(Compare_Local, Nomer, Kol_Alternative);
}

//FINAL_VECTOR_PRIORITY
void Calculate_Final_Priority()
{
	float Sum;
	float Max_Sum = 0;
	for (i=0; i<Kol_Alternative; i++)
	 {
      Sum = 0;
	 for (j=0; j<=7; j++)
	  {
		Sum = Sum + (Vector_Local_Priority[i][j] * Vector_Global_Priority [j]);
	  }
	  Vector_Final_Priority[i] = Sum; 
	  if (Sum > Max_Sum )
	  {
		  Max_Sum = Sum;
		  Good_Alternative = i;
	  }
	 }
}
