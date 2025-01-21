#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <vector>
#include <QStringList>
#include <QPalette>

class LinearSearchGUI : public QWidget {
public:
    LinearSearchGUI(QWidget* parent = nullptr) : QWidget(parent) {
        setupUI();
    }

private slots:
    void searchButtonClicked() {
        int target = targetLineEdit->text().toInt();
        int size = sizeLineEdit->text().toInt();

        if (size <= 0) {
            resultLabel->setText("Invalid size of array.");
            return;
        }

        std::vector<int> numbers(size);
        for (int i = 0; i < size; ++i) {
            numbers[i] = numberLineEdits[i]->text().toInt();
        }

        QStringList steps;
        bool found = false;
        for (int i = 0; i < numbers.size(); ++i) {
            steps.append(QString("Step %1: Checking number %2.").arg(i + 1).arg(numbers[i]));
            if (numbers[i] == target) {
                steps.append(QString("Found Target %1 at Position %2.").arg(target).arg(i + 1));
                colorLineEdit(i, true);
                found = true;
                break;
            }
            else {
                colorLineEdit(i, false);
            }
        }

        if (!found) {
            steps.append("Target not found.");
        }

        resultLabel->setText(steps.join("\n"));
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
        connect(sizeLineEdit, &QLineEdit::textChanged, this, &LinearSearchGUI::sizeChanged); // Connect textChanged signal
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
        QLabel* targetLabel = new QLabel("Enter Target Number:", this);
        targetLayout->addWidget(targetLabel);
        targetLineEdit = new QLineEdit(this);
        targetLayout->addWidget(targetLineEdit);
        layout->addLayout(targetLayout);

        searchButton = new QPushButton("Search", this);
        connect(searchButton, &QPushButton::clicked, this, &LinearSearchGUI::searchButtonClicked);
        layout->addWidget(searchButton);

        resultLabel = new QLabel(this);
        layout->addWidget(resultLabel);

        setLayout(layout);
    }

    void colorLineEdit(int index, bool found) {
        if (index >= 0 && index < numberLineEdits.size()) {
            QLineEdit* lineEdit = numberLineEdits[index];
            QPalette palette = lineEdit->palette();
            if (found) {
                palette.setColor(QPalette::Base, Qt::green);
            }
            else {
                palette.setColor(QPalette::Base, Qt::red);
            }
            lineEdit->setPalette(palette);
        }
    }

    static const int DEFAULT_SIZE = 5;
    static const int MAX_SIZE = 10;

    QLineEdit* sizeLineEdit;
    std::vector<QLineEdit*> numberLineEdits;
    QLineEdit* targetLineEdit;
    QPushButton* searchButton;
    QHBoxLayout* numbersLayout; // Added layout for numbers input boxes
    QLabel* resultLabel;

};