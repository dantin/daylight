# Daylight

Solutions of online judgement

- [POJ](http://poj.org/problemlist)
- [AOJ](http://judge.u-aizu.ac.jp)
- [LeetCode](https://oj.leetcode.com)
- [Daily Coding Problems](https://www.dailycodingproblem.com/)

### C Environment

Default `gcc` in CentOS 7 is `4.8.x`, to use development tools like [AddressSanitizer](https://github.com/google/sanitizers), we need to upgrade `gcc`.

Two way to do this task:

1. use source code
2. use [SCLo](http://www.softwarecollections.org/)

```
# install base package
$ sudo yum install centos-release-scl
# install gcc7
$ sudo yum install devtoolset-7-gcc
# install libasan for gcc7
$ sudo yum install devtoolset-7-libasan-devel
# activate
$ source /opt/rh/devtoolset-7/enable
```

Query

```
# see the path of package installation
$ rpm -ql devtoolset-7libasan-devel
# see runtime info
$ rpm -qf /opt/rh/devtoolset-7/enable
```
