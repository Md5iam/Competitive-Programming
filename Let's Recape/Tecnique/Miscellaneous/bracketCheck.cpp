bool canBeBalanced(string s, int n){
    int count = 0, count_1 = 0;
    for (int i = 0; i < n; i++) {
        if (s[i] == '(')
            count++;
        else
            count--;
        count_1 = min(count_1, count);
    }
    if (count_1 >= -1 && count == 0){
        return true;
    }
    return false;
}
