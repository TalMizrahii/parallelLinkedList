<h1 align="center">
  
![8496952](https://github.com/TalMizrahii/parallelLinkedList/assets/103560553/501dc4f5-570a-4b61-952a-477884518fce)

  Parallel Linked List
  <br>
</h1>

<h4 align="center"> Parallel linked list program, supporting insertion, deletion, retrieval, and length-check operations. </h4>

<p align="center">
  <a href="#description">Description</a> •
  <a href="#implementation">Implementation</a> •
  <a href="#dependencies">Dependencies</a> •
  <a href="#installing-and-executing">Installing And Executing</a> •
  <a href="#author">Author</a> 
</p>

## Description
### About The Program
![download](https://github.com/TalMizrahii/parallelLinkedList/assets/103560553/57393d07-7c87-4ea6-b862-3cf09a4e8442)

This Parallel Linked List program offers a versatile data structure designed for efficient concurrent operations in multi-threaded environments. Leveraging the power of parallel processing, it ensures high-performance execution for tasks such as insertion, deletion, retrieval, and length checking.

The program implements a sorted linked list structure, facilitating rapid binary search-like retrieval and maintaining data integrity. Key features include:

- **Parallel Insertion**: Utilizing OpenMP, the program achieves concurrent insertion of nodes, distributing workload across multiple threads for enhanced speed and efficiency. Each thread operates independently, minimizing contention and maximizing throughput.

- **Thread Safety**: To maintain data consistency and prevent race conditions, the program employs a robust locking mechanism. Each node is equipped with a lock, allowing only one thread at a time to access and modify it. Additionally, a global lock protects critical sections of the linked list, ensuring atomicity during operations.

- **Dynamic Memory Allocation**: The program dynamically allocates memory for nodes and associated locks, optimizing memory usage and facilitating scalability. Memory management is handled efficiently, with resources being deallocated appropriately to prevent memory leaks.

- **Sorted Insertion**: By maintaining the linked list in sorted order, the program enables efficient binary search-like retrieval of values. Insertion operations preserve the sorted property, ensuring that the list remains organized and facilitating rapid data access.

## Implementation

The implementation of the Parallel Linked List is characterized by:

- **Efficient Locking**: Utilizing OpenMP locks, the program ensures thread safety during concurrent operations. Locks are strategically placed to minimize contention and maximize parallelism, striking a balance between performance and data integrity.

- **Optimized Memory Usage**: Dynamic memory allocation enables the program to adapt to varying workloads and data sizes. Memory is allocated and deallocated as needed, preventing wastage and optimizing resource utilization.

- **Scalability**: The program is designed to scale seamlessly with increasing computational resources. Parallel insertion and retrieval operations harness the full potential of multi-core processors, allowing for efficient utilization of available hardware.
  
<img width="506" alt="2" src="https://github.com/TalMizrahii/parallelLinkedList/assets/103560553/f6eb87d0-92da-449f-bd81-f9a0ea0cb5be">

## Dependencies

This program has the following dependencies:

- **OpenMP**: The program utilizes OpenMP for parallelization. Ensure that OpenMP is supported and configured in the compilation environment.

## Installing And Executing

To install and run the program you use [Git](https://git-scm.com). From your command line:

```bash
# Clone this repository.
$ git clone https://github.com/TalMizrahii/parallelLinkedList

# Navigate to the repository directory:
$ cd parallelLinkedList

# Compile the program
$ make

# run the program
$ make run
```
## Author

* [@Tal Mizrahi](https://github.com/TalMizrahii)
* Taltalon1927@gmail.com
