long long int rand46() { // generates 46bit random number
    long long int ret = 0 LL;
    ret |= rand();
    ret |= (((long long int) rand()) << 15);
    assert(0 <= ret);
    assert(ret < INF);
    return ret;
}

