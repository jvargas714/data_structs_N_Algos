#include <iostream>
#include <string>
#include <vector>
using namespace std;

static void display(const vector<int>& vect) {
    for (const auto& el : vect) cout << el << " ";
    cout << endl;
}

/*
 * KMP Algo has two steps
 *  1. preprocessing (or construction of lps)
 *  2. searching phase
 */

/*
 * build lps array for a given pattern
 * Preprocessing Algorithm:
    In the preprocessing part, we calculate values in lps[]. To do that, we keep track of the length of the
    longest prefix suffix value (we use len variable for this purpose)
    for the previous index. We initialize lps[0] and len as 0. If pat[len]
    and pat[i] match, we increment len by 1 and assign the incremented value to lps[i].
    If pat[i] and pat[len] do not match and len is not 0, we update len to lps[len-1].

    finds repeating patterns within the pattern string (informs the search how much to backtrack
    to avoid unecessary searches, indexes should start at 1 for the pattern string
 */
vector<int> preproc(const string& pat) {
    // len of the previous longest prefix suffix
    int len = 0;
    int len_pat = (int)pat.size();

    // lps vector len will be length of the pattern string
    vector<int> lps(pat.size());
    lps[0] = 0;   // lps[0] is always zero
    int i = 1;
    while (i < len_pat) {
        if (pat[i] == pat[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0)
                len = lps[len - 1];
            else {  // len is zero
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}

vector<int> my_preproc(const string& pat) {
    int pat_len = (int)pat.size();
    vector<int> lps(pat_len);
    lps[0] = 0;  // always
    int i = 1;   // starting index
    int len = 0;
    while (i < pat_len) {
        // check for repeating patterns with pat
        if (pat[i] == pat[len])
            lps[i++] = ++len;
        else
            if (len != 0)
                len = lps[len-1];
            else
                lps[i++] = 0;
    }
    return lps;
}

/*
 * time: O(m+n) where m=size of txt, and n = size of pattern string
 */
void kmp(string txt, string pat) {
    vector<int> lps = preproc(pat);
    cout << "lps: ";
    display(lps);
    int i = 0, j = 0;
    int pat_len = (int)pat.size();
    int txt_len = (int)txt.size();
    while (i < txt.size()) {
        // match txt char against pat char
        if (txt[i] == pat[j]) {
            i++; j++;
        }

        // check for a full pattern match
        if (j == pat_len) {
            cout << "found pattern match at index: " << (i-j) << endl;
            j = lps[j-1];  // if found
        } else if (i < txt_len && pat[j] != txt[i]) {  // mismatch after j matches
            if (j!=0)
                j = lps[j-1];  // to avoid extra checks we determine best index for next check
            else
                i++;            // next check will be from beginning of pattern
        }
    }
}

void my_kmp(string txt, string pat) {
    int pat_len = (int)pat.size();
    int txt_len = (int)txt.size();
    int i = 0, j = 0;

    vector<int> lps = my_preproc(pat);

    while (i < txt_len) {
        if (txt[i]==pat[j]) {
            i++;
            j++;
        }

        // check for a pattern match
        if (j==pat_len) {
            cout << "we found a pattern at match index: " << i << endl;
            j = lps[j-1];
        } else if (i < txt_len && pat[j] != txt[i]) {
            if (j!=0) {
                // shift index of j to avoid comparing already compared chars
                j = lps[j-1];
            } else {
                i++;
            }
        }
    }
}

int main() {

    string pat = "cdabcdab";
    string txt = "AABAACAADAABAABA";
    display(preproc(pat));
    my_kmp(txt, pat);
    return 0;
}

/*
    Illustration of preprocessing (or construction of lps[])

    pat[] = "AAACAAAA" yields lps = [0 1 2 0 1 2 3 0]

    len = 0, i  = 0.
    lps[0] is always 0, we move
    to i = 1

    len = 0, i  = 1.
    "AAACAAAA"
    Since pat[len] and pat[i] match, do len++,
    store it in lps[i] and do i++.
    len = 1, lps[1] = 1, i = 2

    len = 1, i  = 2.
    "AAACAAAA"
    Since pat[len] and pat[i] match, do len++,
    store it in lps[i] and do i++.
    len = 2, lps[2] = 2, i = 3

    len = 2, i  = 3.
    AAACAAAA"
    Since pat[len] and pat[i] do not match, and len > 0,
    set len = lps[len-1] = lps[1] = 1

    len = 1, i  = 3.
    "AAACAAAA"
    Since pat[len] and pat[i] do not match and len > 0,
    len = lps[len-1] = lps[0] = 0

    len = 0, i  = 3.
    "AAACAAAA"
    Since pat[len] and pat[i] do not match and len = 0,
    Set lps[3] = 0 and i = 4.
    We know that characters pat
    len = 0, i  = 4.
    Since pat[len] and pat[i] match, do len++,
    store it in lps[i] and do i++.
    len = 1, lps[4] = 1, i = 5

    len = 1, i  = 5.
    Since pat[len] and pat[i] match, do len++,
    store it in lps[i] and do i++.
    len = 2, lps[5] = 2, i = 6

    len = 2, i  = 6.
    Since pat[len] and pat[i] match, do len++,
    store it in lps[i] and do i++.
    len = 3, lps[6] = 3, i = 7

    len = 3, i  = 7.
    Since pat[len] and pat[i] do not match and len > 0,
    set len = lps[len-1] = lps[2] = 2

    len = 2, i  = 7.
    Since pat[len] and pat[i] match, do len++,
    store it in lps[i] and do i++.
    len = 3, lps[7] = 3, i = 8

    We stop here as we have constructed the whole lps[].

 */