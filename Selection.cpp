#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMessageBox>
#include <vector>
#include <QStringList>
#include <QTextEdit>

class SelectionSortGUI : public QWidget {
public:
    SelectionSortGUI(QWidget* parent = nullptr) : QWidget(parent), stepCount(0) {
        setupUI();
    }

private slots:
    void searchButtonClicked() {
        stepCount = 0; // Reset the step count
        int size = sizeLineEdit->text().toInt();

        if (size <= 0) {
            QMessageBox::critical(this, "Error", "Invalid size of array.");
            return;
        }

        std::vector<int> numbers(size);
        for (int i = 0; i < size; ++i) {
            numbers[i] = numberLineEdits[i]->text().toInt();
        }

        // Clear previous steps
        stepsTextEdit->clear();

        // Selection sort and visualize each step
        selectionSort(numbers);

        // Construct a message showing the sorted array
        QString sortedArrayMessage = "Sorted Array: ";
        for (int i = 0; i < size; ++i) {
            sortedArrayMessage += QString::number(numbers[i]);
            if (i < size - 1) {
                sortedArrayMessage += ", ";
            }
        }

        sortedArrayMessage += "\n\nNumber of steps in Selection Sort: " + QString::number(stepCount);

        // Display the sorted array and step count
        stepsTextEdit->setText(sortedArrayMessage);
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
        connect(sizeLineEdit, &QLineEdit::textChanged, this, &SelectionSortGUI::sizeChanged); // Connect textChanged signal
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

        searchButton = new QPushButton("Sort", this); // Change button text to "Sort"
        connect(searchButton, &QPushButton::clicked, this, &SelectionSortGUI::searchButtonClicked);
        layout->addWidget(searchButton);

        // Add QTextEdit to display steps
        stepsTextEdit = new QTextEdit(this);
        stepsTextEdit->setReadOnly(true);
        layout->addWidget(stepsTextEdit);

        setLayout(layout);
    }

    void selectionSort(std::vector<int>& numbers) {
        int n = numbers.size();
        stepCount = 0; // Reset step count
        for (int i = 0; i < n - 1; ++i) {
            int minIndex = i;
            for (int j = i + 1; j < n; ++j) {
                if (numbers[j] < numbers[minIndex]) {
                    minIndex = j;
                }
                // Count only when a swap is performed
            }
            if (minIndex != i) {
                std::swap(numbers[i], numbers[minIndex]);
                // Increment step count when a swap is performed
                ++stepCount;
                // Visualize each step
                visualizeStep(numbers); // Pass numbers vector
            }
        }
    }

    void visualizeStep(const std::vector<int>& numbers) {
        QString stepMessage = "Step " + QString::number(stepCount) + ": ";
        for (int num : numbers) {
            stepMessage += QString::number(num) + " ";
        }
        stepMessage += "\n";
        stepsTextEdit->append(stepMessage);
    }

    static const int DEFAULT_SIZE = 5;
    static const int MAX_SIZE = 10;

    QLineEdit* sizeLineEdit;
    std::vector<QLineEdit*> numberLineEdits;
    QPushButton* searchButton;
    QHBoxLayout* numbersLayout; // Added layout for numbers input boxes

    int stepCount = 0; // Counter for the number of steps in selection sort

    QTextEdit* stepsTextEdit; // Added QTextEdit to display steps
};