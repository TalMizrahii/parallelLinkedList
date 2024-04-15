<h1 align="center">
  
  ![python-logo-glassy](https://user-images.githubusercontent.com/103560553/204082228-92a30920-ca99-4517-9b9d-c3ab44d42a0b.png)

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

This is a parallel implementation of a linked list in C, designed to leverage parallel processing capabilities for faster execution. The program offers functionality for insertion, deletion, retrieval of values, and length checking. It employs OpenMP for parallelization, making it suitable for multi-threaded environments.

## Implementation

The implementation utilizes a sorted linked list structure, ensuring efficient insertion and retrieval operations. Key features include:

- **Parallel Insertion**: Utilizes OpenMP parallelization for concurrent insertion of nodes into the linked list, enhancing performance in multi-core systems.
- **Locking Mechanism**: Implements locks at both node and list level to ensure thread safety during concurrent operations, preventing data corruption.
- **Sorted Insertion**: Maintains the list in sorted order, facilitating binary search-like retrieval and efficient insertion.
- **Dynamic Memory Allocation**: Allocates memory dynamically for nodes and locks, enabling scalability and efficient memory usage.

## Dependencies

This program has the following dependencies:

- **OpenMP**: The program utilizes OpenMP for parallelization. Ensure that OpenMP is supported and configured in the compilation environment.

## Installing And Executing

To install and run the program you use [Git](https://git-scm.com). From your command line:

```bash
# Clone this repository.
$ git clone https://github.com/TalMizrahii/MusicBrains-WebCralwer

# Navigate to the repository directory:
$ cd MusicBrains-WebCrawler

# Run the program
$ python musicrawl.py
```
## Author

* [@Tal Mizrahi](https://github.com/TalMizrahii)
* Taltalon1927@gmail.com
