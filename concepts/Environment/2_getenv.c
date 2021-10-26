#define _GNU_SOURCE
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>

char *_getenv(const char *name)
{
    int i,j;

    char *found = NULL;

    int len_searchkey;
    for (len_searchkey = 0; name[len_searchkey++];); // searchkey_length

    int match = 0;
    for (i = 0; environ[i]; i++)
    {
        for (j = 0; j < len_searchkey; j++)
        {
            if (environ[i][j] != name[j] && environ[i][j] != '=')
            {
                break;
            }

            else if (environ[i][j] == '=')
            {
                match = 1;
                break;
            }
        }

        if (match == 1) // found match
        {
            // get the value by string token.
            // first get the tokenizable array, key_val
            int len_key_val;
            for (len_key_val = 0; environ[j][len_key_val++];); // key_value length

            char key_val[len_key_val];
            for (j = 0; j <= len_key_val; j++)
                key_val[j] = environ[i][j];

            strtok(key_val, "=");
            char *found_tmp = strtok(NULL, "=");

            int len_found;
            for (len_found = 0; found_tmp[len_found++]; );

            found = malloc(len_found * sizeof(char));
            for (j = 0; j < len_found; j++)
                found[j] = found_tmp[j];

            break;
        }
    }

    return found;

}

int main()
{
    char *val = _getenv("PATH");
    puts (val);
}
