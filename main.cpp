#include "functions.cpp"

int main(){
    try{
        std::string delims = " ";
        max_min_t idxs = get_mx_mn_num("laba12.txt", delims);
        swap_strings("laba12.txt", idxs.first, idxs.second);
        std::cout << "String with index " << idxs.first + 1 
        << " swapped with " << idxs.second + 1 << " succesfully"; 
    }
    catch (const char* msg){
        std::cerr << msg;
    }
    return 0;
}
