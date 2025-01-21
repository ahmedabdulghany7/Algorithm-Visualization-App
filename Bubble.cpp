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

class BubbbleSortGUI : public QWidget {
public:
    BubbbleSortGUI(QWidget* parent = nullptr) : QWidget(parent), stepCount(0) {
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

        // Bubble sort and visualize each step
        bubbleSort(numbers);

        // Construct a message showing the sorted array
        QString sortedArrayMessage = "Sorted Array: ";
        for (int i = 0; i < size; ++i) {
            sortedArrayMessage += QString::number(numbers[i]);
            if (i < size - 1) {
                sortedArrayMessage += ", ";
            }
        }

        sortedArrayMessage += "\n\nNumber of steps in Bubble Sort: " + QString::number(stepCount);
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
        connect(sizeLineEdit, &QLineEdit::textChanged, this, &BubbbleSortGUI::sizeChanged); // Connect textChanged signal
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
        connect(searchButton, &QPushButton::clicked, this, &BubbbleSortGUI::searchButtonClicked);
        layout->addWidget(searchButton);

        // Add steps text edit
        stepsTextEdit = new QTextEdit(this);
        stepsTextEdit->setReadOnly(true);
        layout->addWidget(stepsTextEdit);

        setLayout(layout);
    }

    void bubbleSort(std::vector<int>& numbers) {
        int n = numbers.size();
        bool swapped;
        do {
            swapped = false;
            for (int i = 1; i < n; ++i) {
                if (numbers[i - 1] > numbers[i]) {
                    std::swap(numbers[i - 1], numbers[i]);
                    ++stepCount; // Increment step count
                    // Visualize each step
                    visualizeStep(numbers, stepCount); // Pass step count
                    swapped = true;
                }
            }
            --n;
        } while (swapped);
    }

    void visualizeStep(const std::vector<int>& numbers, int stepNumber) { // Accept stepNumber parameter
        QString stepMessage = "Step " + QString::number(stepNumber) + ": "; // Include step number in message
        for (int num : numbers) {
            stepMessage += QString::number(num) + " ";
        }
        stepMessage += "\n\nNumber of steps in Selection Sort: " + QString::number(stepCount);
        stepsTextEdit->append(stepMessage); // Append step message to the text edit
    }

    static const int DEFAULT_SIZE = 5;
    static const int MAX_SIZE = 10;

    QLineEdit* sizeLineEdit;
    std::vector<QLineEdit*> numberLineEdits;
    QPushButton* searchButton;
    QHBoxLayout* numbersLayout; // Added layout for numbers input boxes

    int stepCount = 0; // Counter for the number of steps in bubble sort
    QTextEdit* stepsTextEdit; // Added QTextEdit to display steps

};
