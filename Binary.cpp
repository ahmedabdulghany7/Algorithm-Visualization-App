#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QTextEdit>
#include <vector>
#include <algorithm> // Required for std::sort

class BinarySearchGUI : public QWidget {
public:
    BinarySearchGUI(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private slots:
    void searchButtonClicked() {
        int target = targetLineEdit->text().toInt();
        int size = sizeLineEdit->text().toInt();

        if (size <= 0) {
            //    QMessageBox::critical(this, "Error", "Invalid size of array.");
            return;
        }

        std::vector<int> numbers;
        for (int i = 0; i < size; ++i) {
            numbers.push_back(numberLineEdits[i]->text().toInt());
        }

        std::sort(numbers.begin(), numbers.end()); // Binary search requires sorted array

        // Display sorted numbers in the QTextEdit
        QString sortedNumbersText = "Sorted Numbers:\n";
        for (int num : numbers) {
            sortedNumbersText += QString::number(num) + " ";
        }
        sortedNumbersTextEdit->setText(sortedNumbersText);

        int index = binarySearch(numbers, target);

        if (index != -1) {
            resultTextEdit->setText(QString("Target found at index %1.").arg(index));
        }
        else {
            resultTextEdit->setText("Target not found.");
        }
    }

    void sizeChanged(const QString& newSize) {
        int size = newSize.toInt();
        if (size <= 0 || size > MAX_SIZE) return; // Ensure size is within bounds

        // Clear existing input boxes
        for (auto lineEdit : numberLineEdits) {
            delete lineEdit;
        }
        numberLineEdits.clear();

        // Create new input boxes
        for (int i = 0; i < size; ++i) {
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setPlaceholderText("e.g. 1 2 3 4");
            numberLineEdits.push_back(lineEdit);
            numbersLayout->addWidget(lineEdit); // Add input box horizontally
        }
    }

private:
    void setupUI() {
        QVBoxLayout* layout = new QVBoxLayout(this);

        QHBoxLayout* sizeLayout = new QHBoxLayout;
        QLabel* sizeLabel = new QLabel("Enter size of array:", this);
        sizeLayout->addWidget(sizeLabel);
        sizeLineEdit = new QLineEdit(this);
        sizeLayout->addWidget(sizeLineEdit);
        connect(sizeLineEdit, &QLineEdit::textChanged, this, &BinarySearchGUI::sizeChanged); // Connect textChanged signal
        layout->addLayout(sizeLayout);

        numbersLayout = new QHBoxLayout; // Initialize numbers layout
        QLabel* numbersLabel = new QLabel("Enter numbers separated by space:", this);
        numbersLayout->addWidget(numbersLabel);
        layout->addLayout(numbersLayout);

        for (int i = 0; i < DEFAULT_SIZE; ++i) {
            QLineEdit* lineEdit = new QLineEdit(this);
            lineEdit->setPlaceholderText("e.g. 1 2 3 4");
            numberLineEdits.push_back(lineEdit);
            numbersLayout->addWidget(lineEdit); // Add input box horizontally
        }

        QHBoxLayout* targetLayout = new QHBoxLayout;
        QLabel* targetLabel = new QLabel("Enter target number:", this);
        targetLayout->addWidget(targetLabel);
        targetLineEdit = new QLineEdit(this);
        targetLayout->addWidget(targetLineEdit);
        layout->addLayout(targetLayout);

        searchButton = new QPushButton("Search", this);
        connect(searchButton, &QPushButton::clicked, this, &BinarySearchGUI::searchButtonClicked);
        layout->addWidget(searchButton);

        // Add QTextEdit to display sorted numbers
        sortedNumbersTextEdit = new QTextEdit(this);
        layout->addWidget(sortedNumbersTextEdit);

        // Add QTextEdit to display search result
        resultTextEdit = new QTextEdit(this);
        layout->addWidget(resultTextEdit);

        setLayout(layout);
    }

    int binarySearch(const std::vector<int>& numbers, int target) {
        int left = 0;
        int right = numbers.size() - 1;

        while (left <= right) {
            int mid = left + (right - left) / 2;
            if (numbers[mid] == target) {
                return mid;
            }
            else if (numbers[mid] < target) {
                left = mid + 1;
            }
            else {
                right = mid - 1;
            }
        }
        return -1; // Element not found
    }

    static const int DEFAULT_SIZE = 5;
    static const int MAX_SIZE = 10;

    QLineEdit* sizeLineEdit;
    std::vector<QLineEdit*> numberLineEdits;
    QLineEdit* targetLineEdit;
    QPushButton* searchButton;
    QHBoxLayout* numbersLayout; // Added layout for numbers input boxes
    QTextEdit* sortedNumbersTextEdit; // Added text edit to display sorted numbers
    QTextEdit* resultTextEdit; // Added text edit to display search result
};