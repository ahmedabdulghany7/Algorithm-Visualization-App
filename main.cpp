#include <QApplication>
#include <QWidget>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QDebug>
#include <Linear.cpp>
#include <Binary.cpp>
#include <Bubble.cpp>
#include <Selection.cpp>

class AlgorithmChooser : public QWidget {
public:
    AlgorithmChooser(QWidget* parent = nullptr) : QWidget(parent) {
        setWindowTitle("Algorithm Chooser");
        setFixedSize(700, 200);

        QVBoxLayout* layout = new QVBoxLayout(this);
        QLabel* label = new QLabel("Choose Algorithm", this);
        label->setAlignment(Qt::AlignCenter);
        layout->addWidget(label);

        // Adjust font size
        QFont font = label->font();
        font.setPointSize(14); // Set the desired font size
        label->setFont(font); // Apply the font
        layout->addWidget(label);
        QHBoxLayout* buttonLayout = new QHBoxLayout;

        // Blank space on the left
        buttonLayout->addSpacing(50);

        QVBoxLayout* leftLayout = new QVBoxLayout;
        QPushButton* linearButton = new QPushButton("Linear", this);
        QPushButton* binaryButton = new QPushButton("Binary", this);
        leftLayout->addWidget(linearButton);
        leftLayout->addWidget(binaryButton);
        buttonLayout->addLayout(leftLayout);

        // Add spacing between the left and right layouts
        buttonLayout->addSpacing(40);

        QVBoxLayout* rightLayout = new QVBoxLayout;
        QPushButton* bubbleButton = new QPushButton("Bubble", this);
        QPushButton* selectionButton = new QPushButton("Selection", this);
        rightLayout->addWidget(bubbleButton);
        rightLayout->addWidget(selectionButton);
        buttonLayout->addLayout(rightLayout);

        // Blank space on the right
        buttonLayout->addSpacing(50);

        layout->addLayout(buttonLayout);

        // Add blank space at the bottom
        layout->addSpacing(20);

        connect(linearButton, &QPushButton::clicked, this, &AlgorithmChooser::onLinearButtonClicked);
        connect(binaryButton, &QPushButton::clicked, this, &AlgorithmChooser::onBinaryButtonClicked);
        connect(bubbleButton, &QPushButton::clicked, this, &AlgorithmChooser::onBubbleButtonClicked);
        connect(selectionButton, &QPushButton::clicked, this, &AlgorithmChooser::onSelectionButtonClicked);
    }

private slots:
    void onLinearButtonClicked() {
        LinearSearchGUI* window1 = new LinearSearchGUI; 
        window1->setWindowTitle("Linear Search");
        window1->show();
    }

    void onBinaryButtonClicked() {
        BinarySearchGUI* window2 = new BinarySearchGUI; 
        window2->setWindowTitle("Binary Search");
        window2->show();
    }

    void onBubbleButtonClicked() {
        BubbbleSortGUI* window3 = new BubbbleSortGUI; 
        window3->setWindowTitle("Bubble Sort");
        window3->show();
    }
   
    void onSelectionButtonClicked() {
        SelectionSortGUI* window4 = new SelectionSortGUI; 
        window4->setWindowTitle("Selection Sort");
        window4->show();
    }



};

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);

    AlgorithmChooser window;
    window.show();

    return app.exec();
}
