#include <iostream>
#include <unordered_set>
#include <vector>
#include <string>
#include <set>
#include <cstdlib>

using namespace std;

int main(int argc, char *argv[])
{
  string name = "C-small-attempt0";
  string path = "";

  freopen((path + name + ".in").c_str(), "r", stdin);
  freopen((path + name + ".out").c_str(), "w", stdout);

  int quaternion[5][5] = {{}, 
                          {0, 1, 2, 3, 4},
                          {0, 2, -1, 4, -3},
                          {0, 3, -4, -1, 2},
                          {0, 4, 3, -2, -1}
  };
  
  int test_cases;
  cin >> test_cases;
  for (int test_case = 1; test_case <= test_cases; test_case++) {
    int number;
    cin >> number;

    int count;
    cin >> count;

    int total = count * number;
    string word;
    cin>>word;
    for (int i = 0; i < word.length(); i++) {
      if (word[i] == 'i') word[i] = '2';  
      else if (word[i] == 'j') word[i] = '3';  
      else if (word[i] == 'k') word[i] = '4';  
    }

    string totalWord;
    
    while (count--) {
      totalWord += word;
    }
     
    vector<bool> iCount(total, false); 
    int result = 1;
    int tmp = 1;
    int sign = 1;
    for (int i = 0; i < totalWord.length(); i++) {
      tmp = totalWord[i] - '0';
      result = quaternion[result][tmp];
      sign = result > 0 ? sign : -sign;
      result = abs(result);
      if (sign == 1 && result == 2) {
        iCount[i] = true;
      }
    }

    vector<bool> kCount(total, false); 
    result = 1;
    tmp = 1;
    sign = 1;
    for (int i = totalWord.length() - 1; i >= 0 ; i--) {
      tmp = totalWord[i] - '0';
      result = quaternion[tmp][result];
      sign = result > 0 ? sign : -sign;
      result = abs(result);
      if (sign == 1 && result == 4) {
        kCount[i] = true;
      }
    }
    
    bool ifexist = false;
    int begin = 0;
    while (begin != iCount.size() && iCount[begin] == false) begin++;

    int i, j;
    int end = begin + 2;
    result = 1;
    tmp = 1;
    sign = 1;
    unordered_set<int> position;
    while (end <= kCount.size()) {
      if (kCount[end] == true) {
        i = end - 1;
        j = begin + 1;
        unordered_set<int> tmpSet(position);
        position.clear();
        while (i > j) {
          tmp = totalWord[i] - '0';
          result = quaternion[tmp][result];
          if (iCount[i - 1] == true) {
            position.insert(result);
            if (result == 3) ifexist = true;
          }
          i--;
        }
        

        for (auto index = tmpSet.begin(); index != tmpSet.end(); index++) {
          if (quaternion[*index][result] == 3) ifexist = true;
          else position.insert(quaternion[*index][result]);
          
        }
        while (i > begin) {
          tmp = totalWord[i] - '0';
          result = quaternion[tmp][result];
          if (iCount[i - 1] == true) {
            position.insert(result);
            if (result == 3) ifexist = true;
          }
          i--;
        }


  
        begin = end; 
      }

      end++;
      if (ifexist) break;
    }
    //if (end <= kCount.size()) {
    //  int i
    //}

    cout << "Case #" << test_case << ": " << (ifexist ? "YES" : "NO") << endl;
    cout.flush();
  }
  fclose(stdout);
  fclose(stdin);
  return 0;
}
