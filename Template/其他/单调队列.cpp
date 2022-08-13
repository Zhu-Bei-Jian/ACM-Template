//单调队列
struct node
{
    int id;
    int val;
};
struct My_deque
{
    node a[MAXN];
    int L, R;
    My_deque() { L = 1; R = 0; }

    int size() { return this->R-this->L+1; }
    bool empty() { return this->size() == 0; }
    void push_back(node x) {
        a[++R] = x;
    }
    node back() {
        return this->a[R];
    }
    node front()
    {
        return this->a[L];
    }
    void pop_back() {
        --R;
    }
    void pop_front() {
        ++L;
    }
    void clear() {
        L = 1; R = 0;
    }
}q;





//
//最小值

    for (int i = 1; i <= n; i++)
    {
        while (!q.empty() && q.back().val >= a[i].val) {
            q.pop_back();
        }
        q.push_back(a[i]);

        while (q.front().id < i - k + 1)q.pop_front();
        if (i >= k)
            printf("%d%c", q.front().val, i == n ? '\n' : ' ');

    }