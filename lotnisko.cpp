//Dominik Łempicki Kapitan

#include <iostream>
#include <vector>
#include <algorithm>

using std::cin;
using std::cout;

struct dlugosc_lotniska {
    int dlugosc{ 0 };
    int pozycjay{ 0 };
    int pozycjax{ 0 };
    bool pion{ false };
};

bool czy_poloczone(int x_1, int y_1, int x_2, int y_2, int dlugosc, bool polozenie_1, bool polozenie_2) {
    if ((std::min(x_1, x_2) >= std::max(x_1, x_2) && std::min(y_1, y_2) >= std::max(y_1, y_2)) || (((x_1 * x_2) - (y_2 * y_2)) == 0)) return true;
    return false;
}

int najdluzsze(const std::vector<dlugosc_lotniska>& dlugosci_lotnisk) {
    for (int i = 0; i < dlugosci_lotnisk.size() - 1; i++) {
        if (dlugosci_lotnisk[i].dlugosc >= dlugosci_lotnisk[i + 1].dlugosc) {
            if (!czy_poloczone(dlugosci_lotnisk[i].pozycjax, dlugosci_lotnisk[i].pozycjay, dlugosci_lotnisk[i + 1].pozycjax, dlugosci_lotnisk[i + 1].pozycjay, dlugosci_lotnisk[i].dlugosc, dlugosci_lotnisk[i].pion, dlugosci_lotnisk[i + 1].pion))
            {
                if (i != 0) {
                    if (((dlugosci_lotnisk[i - 1].dlugosc) / 2) > dlugosci_lotnisk[i].dlugosc && dlugosci_lotnisk[i - 1].dlugosc != dlugosci_lotnisk[i].dlugosc)
                    {
                        return (dlugosci_lotnisk[i - 1].dlugosc / 2);
                    }
                }
                return dlugosci_lotnisk[i+1].dlugosc;
            }
        }
    }
    return 0;
}

int main() {
        std::ios_base::sync_with_stdio(0);
        std::cin.tie(0);

        int szerokosc{ 0 }, liczba_pasow{ 0 };
        cin >> szerokosc >> liczba_pasow;

        std::vector<std::vector<bool>> plan_lotniska(szerokosc, std::vector<bool>(szerokosc));

        for (int i = 0; i < szerokosc; i++) {
            for (int j = 0; j < szerokosc; j++) {
                char tmp;
                cin >> tmp;
                if (tmp == 'X') plan_lotniska[i][j] = 1;
                else plan_lotniska[i][j] = 0;
            }
        }

        std::vector<dlugosc_lotniska> dlugosci_lotnisk;

        for (int i = 0; i < szerokosc; i++) {
            int ile_dlugie{ 0 };
            for (int j = 0; j < szerokosc; j++) {
                if (plan_lotniska[i][j] == false) ile_dlugie++;
                if ((plan_lotniska[i][j] == true || j == szerokosc - 1) && ile_dlugie != 0) {
                    if (j == szerokosc - 1) dlugosci_lotnisk.push_back({ ile_dlugie, i, j - ile_dlugie + 1, false });
                    else dlugosci_lotnisk.push_back({ ile_dlugie, i, j - ile_dlugie, false });
                    ile_dlugie = 0;
                }
            }
        }

        for (int i = 0; i < szerokosc; i++) {
            int ile_dlugie{ 0 };
            for (int j = 0; j < szerokosc; j++) {
                if (plan_lotniska[j][i] == false) ile_dlugie++;
                if ((plan_lotniska[j][i] == true || j == szerokosc - 1) && ile_dlugie != 0) {
                    if (j == szerokosc - 1) dlugosci_lotnisk.push_back({ ile_dlugie, j - ile_dlugie + 1, i, true });
                    else dlugosci_lotnisk.push_back({ ile_dlugie, j - ile_dlugie, i, true });
                    ile_dlugie = 0;
                }
            }
        }

        std::sort(dlugosci_lotnisk.begin(), dlugosci_lotnisk.end(), [](const dlugosc_lotniska& a, const dlugosc_lotniska& b) {return a.dlugosc > b.dlugosc;});

        if (liczba_pasow == 1) cout << dlugosci_lotnisk[0].dlugosc;
        else if (liczba_pasow == 2) cout << najdluzsze(dlugosci_lotnisk);
        else cout << 0;

    return 0;
}
