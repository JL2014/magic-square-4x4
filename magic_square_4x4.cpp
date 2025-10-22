// g++ -o magic_square_4x4 magic_square_4x4.cpp -lflint && ./magic_square_4x4
#include <bits/stdc++.h>
#include <flint/fmpz.h>
using namespace std;

unsigned int i, j, k, max_len;

// Teste si une matrice 4x4 d'entiers fmpz est magique
bool isMagic(const vector<vector<fmpz*>>& M) {
    fmpz_t s, tmp;
    fmpz_init(s);
    fmpz_init(tmp);

    // somme de la première ligne
    fmpz_zero(s);
    for (j = 0; j < 4; ++j) fmpz_add(s, s, M[0][j]);

    // lignes
    for (i = 0; i < 4; ++i) {
      fmpz_zero(tmp);
      for (j = 0; j < 4; ++j) fmpz_add(tmp, tmp, M[i][j]);
      if (fmpz_cmp(tmp, s) != 0) {
        fmpz_clear(s); fmpz_clear(tmp);
        return false;
      }
    }

    // colonnes
    for (j = 0; j < 4; ++j) {
      fmpz_zero(tmp);
      for (i = 0; i < 4; ++i) fmpz_add(tmp, tmp, M[i][j]);
      if (fmpz_cmp(tmp, s) != 0) {
        fmpz_clear(s); fmpz_clear(tmp);
        return false;
      }
    }

    // diagonales
    fmpz_zero(tmp);
    for (i = 0; i < 4; ++i) fmpz_add(tmp, tmp, M[i][i]);
    if (fmpz_cmp(tmp, s) != 0) {
      fmpz_clear(s); fmpz_clear(tmp);
      return false;
    }

    fmpz_zero(tmp);
    for (i = 0; i < 4; ++i) fmpz_add(tmp, tmp, M[i][3 - i]);
    if (fmpz_cmp(tmp, s) != 0) {
      fmpz_clear(s); fmpz_clear(tmp);
      return false;
    }

    fmpz_clear(s);
    fmpz_clear(tmp);
    return true;
}

// Applique les permutations p et q à une matrice A
vector<vector<fmpz*>> permute(const vector<vector<fmpz*>>& A,
                              const vector<int>& p,
                              const vector<int>& q) {
    vector<vector<fmpz*>> M(4, vector<fmpz*>(4));
    for (i = 0; i < 4; ++i) {
      for (j = 0; j < 4; ++j) {
        M[i][j] = new fmpz;
        fmpz_init(M[i][j]);
        fmpz_set(M[i][j], A[p[i]][q[j]]);
      }
    }
    return M;
}

int main(int argc, char* argv[]) {
    const char* default_values[16] = {
      "68","29","41","37",
      "17","31","79","32",
      "59","28","23","61",
      "11","77", "8","49"
    };
    const char** input_values = default_values;

    if (argc == 17) input_values = const_cast<const char**>(argv + 1);
    else if (argc != 1) {
      cerr << "Usage: " << argv[0] << " [16 entiers]" << endl
           << "Aucune entrée → carré magique par défaut." << endl;
      return 1;
    }

    for (i = 0, k = 0, max_len = 0; i < 4; ++i) {
      for (j = 0; j < 4; ++j, ++k) {
        max_len = max((unsigned int) max_len, (unsigned int) strlen(input_values[k]));
      }
    }

    vector<vector<fmpz*>> A(4, vector<fmpz*>(4)), B(4, vector<fmpz*>(4));
    for (i = 0, k = 0; i < 4; ++i) {
      for (j = 0; j < 4; ++j, ++k) {
        B[i][j] = new fmpz;
        A[i][j] = new fmpz;
        fmpz_init(B[i][j]);
        fmpz_init(A[i][j]);
        fmpz_set_str(B[i][j], input_values[k], 10);
        fmpz_mul(A[i][j], B[i][j], B[i][j]);
      }
    } // A = B^2

    // Génération des permutations
    vector<int> base = {0,1,2,3};
    vector<vector<int>> perms;
    do perms.push_back(base); while (next_permutation(base.begin(), base.end()));

    int count = 0;
    for (auto& p : perms) {
      for (auto& q : perms) {
        auto M = permute(A, p, q);
        if (isMagic(M)) {
          ++count;
          cout << "--- Matrice " << count << " ---" << endl;
          cout << "row=("; for (int i=0;i<4;i++) cout << p[i] << (i<3?",":""); cout << "), ";
          cout << "col=("; for (int i=0;i<4;i++) cout << q[i] << (i<3?",":""); cout << ")" << endl;
          for (i=0;i<4;i++) {
            cout << "  | ";
            for (j=0;j<4;j++) {
              char* b=fmpz_get_str(nullptr, 10, B[p[i]][q[j]]);
              char* v=fmpz_get_str(nullptr, 10, A[p[i]][q[j]]);
              cout << setw(max_len) << b << "^2(" << setw(max_len+max_len) << v << ") ";
              flint_free(b); flint_free(v);
            }
            cout << "|" << endl;
          }
          cout << endl;
        }
        for (auto& row : M) for (auto* x : row) { fmpz_clear(x); delete x; }
      }
    }

    cerr << "Total: " << count << " matrices magiques trouvées." << endl;

    for (auto& row : A) for (auto* x : row) { fmpz_clear(x); delete x; }
    for (auto& row : B) for (auto* x : row) { fmpz_clear(x); delete x; }

    return count ? 0 : 2;
}
