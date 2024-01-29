#include <iostream>
#include <vector>

typedef struct clausula {
    char literal[3];
    bool negated[3];
} clausula;

typedef vector<clausula> v_clausula
typedef vector<bool> v_literal

// Donada una combinacio de literals, verifica si satisfa el conjunt.
bool verificar (const v_clausula& conj, const v_clausula& cert) {
    for (int i = 0; i < conj.size(); ++i) {
        clausula c = conj[i];
        for (int j = 0; j < 3; ++j) {
            // Si un literal esta negat i al certificat no, llavors no val.
            if (c.negated[j] == cert[c.literal[j]-'a']) return false;
        }
    }
    return true;
}

// Escriu un certificat per stdout.
void escriu_certificat (const v_literal& cert) {
    for (int i = 0; i < cert.size(); ++i) {
        if (i != 0) cout << ' ';
        if (not cert[i]) cout << '-';
        cout << 'a'+i;
    }
    cout << endl;
}

// Genera combinacions de literals i les verifica. Si una combinacio satisfa el conjunt, la escriu per stdout.
void generar_combinacions (const v_clausula& conj, v_literal& cert, int idx) {
    if (idx == cert.size()) {
        if (verificar(conj, cert)) escriu_certificat(cert);
        return;
    }
    cert[idx] = true;
    generar_combinacions(conjunt, certificat, idx+1);
    cert[idx] = false;
    generar_combinacions(conjunt, certificat, idx+1);
}

// Main.
int main (void) {
    int n, m;
    cin >> n >> m;

    v_literal certificat (n, true);
    v_clausula conjunt (m);

    for (int i = 0; i < m; ++i) {
        // Llegir clausules
    }

    generar_combinacions(conjunt, certificat, 0);
}
