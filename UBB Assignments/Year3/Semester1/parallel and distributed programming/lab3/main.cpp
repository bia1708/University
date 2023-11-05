#include <iostream>
#include <vector>
#include <thread>
#include <future>
#include <chrono>

const int N = 9; // Matrix size

// Function to compute a single element of the resulting matrix
int computeElement(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, int row, int col) {
    int result = 0;
    for (int i = 0; i < N; ++i) {
        result += A[row][i] * B[i][col];
    }
    return result;
}

// Method 1: Each task computes consecutive rows
void parallelMatrixMultiplicationConsecutiveRows(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int taskID, int numTasks) {
    for (int i = taskID; i < N; i += numTasks) {
        for (int j = 0; j < N; ++j) {
            C[i][j] = computeElement(A, B, i, j);
        }
    }
}

// Method 2: Each task computes consecutive columns
void parallelMatrixMultiplicationConsecutiveCols(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int taskID, int numTasks) {
    for (int j = taskID; j < N; j += numTasks) {
        for (int i = 0; i < N; ++i) {
            C[i][j] = computeElement(A, B, i, j);
        }
    }
}

// Method 3: Each task takes every k-th element
void parallelMatrixMultiplicationKthElement(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int taskID, int numTasks) {
    for (int i = taskID; i < N; i += numTasks) {
        for (int j = 0; j < N; j += numTasks) {
            for (int row = i; row < N && row < i + numTasks; ++row) {
                for (int col = j; col < N && col < j + numTasks; ++col) {
                    C[row][col] = computeElement(A, B, row, col);
                }
            }
        }
    }
}

// Thread-per-task approach
void matrixMultiplicationThreadPerTask(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int numTasks, void (*multiplyFunction)(const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, int, int)) {
    std::vector<std::thread> threads;
    for (int i = 0; i < numTasks; ++i) {
        threads.push_back(std::thread(multiplyFunction, A, B, std::ref(C), i, numTasks));
    }
    for (auto& thread : threads) {
        thread.join();
    }
}

// Thread pool approach
void matrixMultiplicationThreadPool(const std::vector<std::vector<int>>& A, const std::vector<std::vector<int>>& B, std::vector<std::vector<int>>& C, int numTasks, void (*multiplyFunction)(const std::vector<std::vector<int>>&, const std::vector<std::vector<int>>&, std::vector<std::vector<int>>&, int, int)) {
    std::vector<std::future<void>> futures;
    for (int i = 0; i < numTasks; ++i) {
        futures.push_back(std::async(std::launch::async, multiplyFunction, std::ref(A), std::ref(B), std::ref(C), i, numTasks));
    }
    for (auto& future : futures) {
        future.get();
    }
}

int main() {
    // Initialize matrices A and B, and result matrix C
    std::vector<std::vector<int>> A(N, std::vector<int>(N));
    std::vector<std::vector<int>> B(N, std::vector<int>(N));
    std::vector<std::vector<int>> C(N, std::vector<int>(N));

    std::cout << "A:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            A[i][j] = i;
            std::cout << A[i][j] << " ";
        }
        std::cout << "\n";
    }

    std::cout << "\nB:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            B[i][j] = j;
            std::cout << B[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Choose a method for splitting the work and an approach (thread-per-task or thread pool)
    int numTasks = 4; // Number of tasks

    auto start1 = std::chrono::high_resolution_clock::now();
    matrixMultiplicationThreadPerTask(A, B, C, numTasks, parallelMatrixMultiplicationConsecutiveRows);
    auto end1 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration1 = end1 - start1;

    auto start2 = std::chrono::high_resolution_clock::now();
    matrixMultiplicationThreadPerTask(A, B, C, numTasks, parallelMatrixMultiplicationConsecutiveCols);
    auto end2 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration2 = end2 - start2;

    auto start3 = std::chrono::high_resolution_clock::now();
    matrixMultiplicationThreadPerTask(A, B, C, numTasks, parallelMatrixMultiplicationKthElement);
    auto end3 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration3 = end3 - start3;

    auto start4 = std::chrono::high_resolution_clock::now();
    matrixMultiplicationThreadPool(A, B, C, numTasks, parallelMatrixMultiplicationConsecutiveRows);
    auto end4 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration4 = end4 - start4;

    auto start5 = std::chrono::high_resolution_clock::now();
    matrixMultiplicationThreadPool(A, B, C, numTasks, parallelMatrixMultiplicationConsecutiveCols);
    auto end5 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration5 = end5 - start5;

    auto start6 = std::chrono::high_resolution_clock::now();
    matrixMultiplicationThreadPool(A, B, C, numTasks, parallelMatrixMultiplicationKthElement);
    auto end6 = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration6 = end6 - start6;

//    matrixMultiplicationThreadPerTask(A, B, C, numTasks, parallelMatrixMultiplicationConsecutiveRows);
//    matrixMultiplicationThreadPool(A, B, C, numTasks, parallelMatrixMultiplicationConsecutiveRows);

    std::cout << "\nC:\n";
    for(int i = 0; i < N; i++) {
        for(int j = 0; j < N; j++) {
            std::cout << C[i][j] << " ";
        }
        std::cout << "\n";
    }

    // Create a table to show the execution times
    std::cout << "Method\t\t\tApproach\t\tExecution Time (seconds)\n";
    std::cout << "---------------------------------------------------------\n";
    std::cout << "Consecutive Rows\tThread-per-Task\t" << duration1.count() << " seconds\n";
    std::cout << "Consecutive Columns\tThread-per-Task\t" << duration2.count() << " seconds\n";
    std::cout << "Every k-th Element\tThread-per-Task\t" << duration3.count() << " seconds\n";
    std::cout << "Consecutive Rows\tThread Pool\t" << duration4.count() << " seconds\n";
    std::cout << "Consecutive Columns\tThread Pool\t" << duration5.count() << " seconds\n";
    std::cout << "Every k-th Element\tThread Pool\t" << duration6.count() << " seconds\n";
    return 0;
}
