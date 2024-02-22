#include <QMainWindow>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTableWidget>
#include <QHeaderView>
#include <QFileDialog>
#include <QStackedWidget>

#include "form.h"
#include "searchform.h"
#include "validator.h"


class MainWindow : public QMainWindow
{
    Q_OBJECT

private:
    int currentRow;

    Form *form;
    SearchForm *searchForm;
    Validator validator;

    QStackedWidget *stackedWidget;
    QTableWidget* table;
    QWidget *bar;
    QWidget *menu;

    void NewForm();
    void NewSearchForm();

    void HideForm();
    void HideSearchForm();

    void ShowForm();
    void ShowErrorMessage(const QString text);
    void BackToForm(int result);

    void ClearTable();
    QString ValidateFormData();
    bool CheckRowBySearch(int rowId);

    void CreateTable();
    void CreateBar();
    void CreateMenu();

    void FormToTableRow();
    void TableRowToForm();

    void TableToFile(QFile *file);
    void FileToTable(QFile *file);

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void NewTable();
    void ImportFromFile();
    void SaveToFile();

    void NewContact();
    void EditContact(QTableWidgetItem* item);
    void DeleteContacts();
    void SaveContact();

    void ShowSearchForm();
    void SearchContacts();
    void ClearSearchForm();

    void ToMenu();
};
