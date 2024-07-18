#include <iostream>
1
2
3
4
5
6
7
8
9
10
11
12
13
14
15
16
17
18
19
20
21
22
23
24
25
26
27
28
29
30
31
32
33
34
35
36
37
38
39
40
41
42
43
44
45
46
47
48
49
50
51
52
53
54
55
56
57
58
59
60
61
62
63
64
65
66
67
68
69
70
71
72
73
74
75
76
77
78
79
80
81
82
83
84
85
86
87
88
89
90
91
92
93
94
95
96
97
98
99
100
101
102
103
104
105
106
107
108
109
110
111
112
113
114
115
116
117
118
119
120
121
122
123
124
125
126
127
128
129
130
131
132
133
134
135
136
137
138
139
140
141
142
143
144
145
146
147
148
149
150
151
152
153
154
155
156
157
158
159
160
161
162
163
164
165
166
167
168
169
170
171
172
173
174
175
176
177
178
179
180
181
182
183
184
185
186
187
188
189
190
191
192
193
194
195
196
197
198
199
200
201
202
203
204
205
206
207
208
209
210
211
212
213
214
215
216
217
218
219
220
221
222
223
224
225
226
227
228
229
230
231
232
233
234
235
236
237
238
239
240
241
242
243
244
245
246
247
248
249
250
251
252
253
254
255
256
257
258
259
260
261
262
263
264
265
266
267
268
269
270
271
272
273
274
275
276
277
278
279
280
281
282
283
284
285
286
287
288
289
290
291
292
293
294
295
296
297
298
299
300
301
302
303
304
305
306
307
308
309
310
311
312
313
314
315
316
317
318
319
320
321
322
323
324
325
326
327
328
329
330
331
332
333
334
335
336
337
338
339
340
341
342
343
344
345
346
347
348
349
350
351
352
353
354
355
356
357
358
359
360
361
362
363
364
365
366
367
368
369
370
371
372
373
374
375
376
377
378
379
380
381
382
383
384
385
386
387
388
389
390
391
392
393
394
395
396
397
398
399
400
401
402
403
404
405
406
407
408
409
410
411
412
413
414
415
416
417
418
419
420
421
422
423
424
425
426
427
428
429
430
431
432
433
434
435
436
437
438
439
440
441
442
443
444
445
446
447
448
449
450
451
452
453
454
455
456
457
458
459
460
461
462
463
464
465
466
467
468
469
470
471
472
473
474
475
476
477
478
479
480
481
482
483
484
485
486
487
488
489
490
491
492
493
494
495
496
497
498
499
500
501
502
503
504
505
506
507
508
509
510
511
512
513
514
515
516
517
518
519
520
521
522
523
524
525
526
527
528
529
530
531
532
533
534
535
536
537
538
539
540
541
542
543
544
545
546
547
548
549
550
551
552
553
554
555
556
557
558
559
560
561
562
563
564
565
566
567
568
569
570
571
572
573
574
575
576
577
578
579
580
581
582
583
584
585
586
587
588
589
590
591
592
593
594
595
596
597
598
599
600
601
602
603
604
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>

using namespace std;

class CostumeRental; // Forward declaration

// Costume ADT
class Costume {
public:
    int costumeID;
    string costumeName;
    int size;
    string costumeFit;
    int numberOfCopies;

    Costume(int id, string n, int s, string f, int num)
        : costumeID(id), costumeName(n), size(s), costumeFit(f), numberOfCopies(num) {}

    void display() const {
        cout << "Costume ID: " << costumeID << "\nCostume Name: " << costumeName << "\nSize: " << size
             << "\nCostume Fit (Adult/Child): " << costumeFit << "\nNumber of Copies: " << numberOfCopies << endl;
    }

    static void addCostume(CostumeRental &store, int id, string costumeName, int size, string fit, int copies);
    static void rentCostume(CostumeRental &store, int customerID, int costumeID);
    static void returnCostume(CostumeRental &store, int customerID);
    static void showCostumeDetails(CostumeRental &store, int costumeID);
    static void displayAllCostumes(CostumeRental &store);
    static void checkCostumeAvailability(CostumeRental &store, int costumeID);
};

// Customer ADT
class Customer {
public:
    int customerID;
    string name;
    string address;

    Customer(int id, string n, string a)
        : customerID(id), name(n), address(a) {}

    void display() const {
        cout << "Customer ID: " << customerID << "\nName: " << name << "\nAddress: " << address << endl;
    }

    static void addCustomer(CostumeRental &store, int id, string name, string address);
    static void showCustomerDetails(CostumeRental &store, int customerID);
    static void listAllCustomers(CostumeRental &store);
    static void listAllCostumesRentedByCustomer(CostumeRental &store, int customerID);
};

// CustomerRent ADT (inherits from Customer)
class CustomerRent : public Customer {
public:
    list<int> rentedCostumes;

    CustomerRent(int id, string n, string a) : Customer(id, n, a) {}

    void rentCostume(int costumeID) {
        rentedCostumes.push_back(costumeID);
    }

    void returnCostume(int costumeID) {
        rentedCostumes.remove(costumeID);
    }

    void displayRentedCostumes() const {
        cout << "Costumes rented by Customer ID " << customerID << ":\n";
        for (list<int>::const_iterator it = rentedCostumes.begin(); it != rentedCostumes.end(); ++it) {
            cout << "Costume ID: " << *it << endl;
        }
    }

    void returnAllCostumes() {
        rentedCostumes.clear();
    }
};

// CostumeRental class to manage all operations
class CostumeRental {
private:
    deque<Costume> costumes;
    deque<CustomerRent> customers;
    int costumeCounter;
    int customerCounter;

public:
    CostumeRental() : costumeCounter(0), customerCounter(0) {
        loadCostumes();
        loadCustomers();
        loadCustomerRents();
    }

    void loadCostumes();
    void loadCustomers();
    void loadCustomerRents();
    void saveCostumes();
    void saveCustomers();
    void saveCustomersRents();
    void menu(); // Declare the menu function

    friend class Costume;
    friend class Customer;
};

// Costume ADT operations implementation
void Costume::addCostume(CostumeRental &store, int id, string costumeName, int size, string fit, int copies) {
    store.costumes.push_back(Costume(id, costumeName, size, fit, copies));
    store.saveCostumes();
    cout << "Costume added successfully.\n" << endl;
}

void Costume::rentCostume(CostumeRental &store, int customerID, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            if (it->numberOfCopies > 0) {
                it->numberOfCopies--;
                for (deque<CustomerRent>::iterator cit = store.customers.begin(); cit != store.customers.end(); ++cit) {
                    if (cit->customerID == customerID) {
                        cit->rentCostume(costumeID);
                        store.saveCostumes();
                        store.saveCustomersRents();
                        cout << "Costume rented successfully.\n" << endl;
                        return;
                    }
                }
                cout << "Customer not found.\n" << endl;
                return;
            } else {
                cout << "Costume not available.\n" << endl;
                return;
            }
        }
    }
    cout << "Costume not found.\n" << endl;
}

void Costume::returnCostume(CostumeRental &store, int customerID) {
    for (deque<CustomerRent>::iterator cit = store.customers.begin(); cit != store.customers.end(); ++cit) {
        if (cit->customerID == customerID) {
            cit->displayRentedCostumes();
            for (list<int>::iterator it = cit->rentedCostumes.begin(); it != cit->rentedCostumes.end(); ++it) {
                for (deque<Costume>::iterator vit = store.costumes.begin(); vit != store.costumes.end(); ++vit) {
                    if (vit->costumeID == *it) {
                        vit->numberOfCopies++;
                    }
                }
            }
            cit->returnAllCostumes();
            store.saveCostumes();
            store.saveCustomersRents();
            cout << "All costumes returned successfully.\n" << endl;
            return;
        }
    }
    cout << "Customer not found.\n" << endl;
}

void Costume::showCostumeDetails(CostumeRental &store, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            return;
        }
    }
    cout << "Costume with ID " << costumeID << " not found.\n" << endl;
}

void Costume::displayAllCostumes(CostumeRental &store) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        it->display();
        cout << endl;
    }
    
}

void Costume::checkCostumeAvailability(CostumeRental &store, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            cout << "Number of copies available: " << it->numberOfCopies << "\n";
            if (it->numberOfCopies > 0) {
                cout << "Status: Available\n" << endl;
            } else {
                cout << "Status: Not Available\n" << endl;
            }
            return;
        }
    }
    cout << "Costume not found.\n" << endl;
}

// Customer ADT operations implementation
void Customer::addCustomer(CostumeRental &store, int id, string name, string address) {
    store.customers.push_back(CustomerRent(id, name, address));
    store.saveCustomers();
    cout << "Customer added successfully.\n" << endl;
}

void Customer::showCustomerDetails(CostumeRental &store, int customerID) {
    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        if (it->customerID == customerID) {
            it->display();
            return;
        }
    }
    cout << "Customer not found.\n" << endl;
}

void Customer::listAllCustomers(CostumeRental &store) {
    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        it->display();
        cout << endl;
    }
}

void Customer::listAllCostumesRentedByCustomer(CostumeRental &store, int customerID) {
    bool customerFound = false;

    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        if (it->customerID == customerID) {
            customerFound = true;
            if (it->rentedCostumes.empty()) {
                cout << "Customer ID " << customerID << " has not rented any costumes.\n" << endl;
            } else {
                it->displayRentedCostumes();
            }
            return;
        }
    }
    if (!customerFound) {
        cout << "Customer not found.\n" << endl;
    }
}

// CostumeRental class function implementations
void CostumeRental::loadCostumes() {
    ifstream inFile("costumes.txt");
    if (!inFile) {
        cerr << "Error opening costumes file.\n" << endl;
        return;
    }

    int id, size, copies;
    string costumeName, fit;
    while (inFile >> id) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, costumeName);
        inFile >> size;
        inFile.ignore(); // Ignore the newline character
        getline(inFile, fit);
        inFile >> copies;
        costumes.push_back(Costume(id, costumeName, size, fit, copies));
    }
    inFile.close();
}

void CostumeRental::loadCustomers() {
    ifstream inFile("customers.txt");
    if (!inFile) {
        cerr << "Error opening customers file.\n" << endl;
        return;
    }

    int id;
    string name, address;
    while (inFile >> id) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, name);
        getline(inFile, address);
        customers.push_back(CustomerRent(id, name, address));
    }
    inFile.close();
}

void CostumeRental::loadCustomerRents() {
    ifstream inFile("customer_rents.txt");
    if (!inFile) {
        cerr << "Error opening customer rents file.\n" << endl;
        return;
    }

    int customerID, costumeID;
    while (inFile >> customerID >> costumeID) {
        for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
            if (it->customerID == customerID) {
                it->rentCostume(costumeID);
                break;
            }
        }
    }
    inFile.close();
}

void CostumeRental::saveCostumes() {
    ofstream outFile("costumes.txt");
    if (!outFile) {
        cerr << "Error opening costumes file for writing.\n" << endl;
        return;
    }

    
    outFile << "Costumes Data File\n"; //labeling text for text file
    outFile << "ID | Name | Size | Fit | NumberOfCopies\n"; //labeling text for text file

    for (deque<Costume>::iterator it = costumes.begin(); it != costumes.end(); ++it) {
        outFile << it->costumeID << "  | " << it->costumeName << " | "
                << it->size << " | " << it->costumeFit << " | "
                << it->numberOfCopies << endl;
    }
    outFile.close();
}

void CostumeRental::saveCustomers() {
    ofstream outFile("customers.txt");
    if (!outFile) {
        cerr << "Error opening customers file for writing.\n" << endl;
        return;
    }

    
    outFile << "Customers Data File\n"; //labeling text for text file
    outFile << "ID | Name | Address\n"; //labeling text for text file

    for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
        outFile << it->customerID << "  | " << it->name << " | "
                << it->address << endl;
    }
    outFile.close();
}

void CostumeRental::saveCustomersRents() {
    ofstream outFile("customer_rents.txt");
    if (!outFile) {
        cerr << "Error opening customer rents file for writing.\n" << endl;
        return;
    }

    outFile << "Customer Rents Data File\n"; //labeling text for text file
    outFile << "CustomerID | CostumeID\n"; //labeling text for text file

    for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
        for (list<int>::iterator vit = it->rentedCostumes.begin(); vit != it->rentedCostumes.end(); ++vit) {
            outFile << it->customerID << " | " << *vit << endl;
        }
    }
    outFile.close();
}

void CostumeRental::menu() {
    int choice;
    do {
        cout << "======================================"<< endl;
        cout << "Costume Rental System Menu:\n";
        cout << "======================================"<< endl;
        cout << "1. New Costume\n";
        cout << "2. Rent a Costume\n";
        cout << "3. Return a Costume\n";
        cout << "4. Show Costume Details\n";
        cout << "5. Display All Costumes\n";
        cout << "6. Check Costume Availability\n";
        cout << "7. Customer Maintenance\n";
        cout << "8. Exit\n";
        cout << "======================================"<< endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "======================================"<< endl;

        switch (choice) {
            case 1: {
                int id;
                string costumeName;
                int size;
                string fit;
                int copies;
                cout << "Enter costume ID: ";
                cin >> id;
                cout << "Enter costume name: ";
                cin.ignore(); // Ignore any remaining newline character in the buffer
                getline(cin, costumeName);
                cout << "Enter size: ";
                cin >> size;
                cout << "Enter fit (Adult/Child): ";
                cin.ignore(); // Ignore any remaining newline character in the buffer
                getline(cin, fit);
                cout << "Enter number of copies: ";
                cin >> copies;
                Costume::addCostume(*this, id, costumeName, size, fit, copies);
                break;
            }
            case 2: {
                int customerID, costumeID;
                cout << "Enter customer ID: ";
                cin >> customerID;
                Customer::showCustomerDetails(*this, customerID);
                char rentAgain;
                do {
                    cout << "Enter costume ID: ";
                    cin >> costumeID;
                    Costume::rentCostume(*this, customerID, costumeID);
                    cout << "Do you want to rent another costume? (Y/N): ";
                    cin >> rentAgain;
                } while (rentAgain == 'Y' || rentAgain == 'y');
                break;
            }
            case 3: {
                int customerID;
                cout << "======================================"<< endl;
                cout << "Enter customer ID: ";
                cin >> customerID;
                cout << "======================================"<< endl;
                Costume::returnCostume(*this, customerID);
                break;
            }
            case 4: {
                int costumeID;
                cout << "======================================"<< endl;
                cout << "Enter costume ID: ";
                cin >> costumeID;
                Costume::showCostumeDetails(*this, costumeID); 
                break;
            }
            case 5: {
                if(costumes.empty()){
                    cout << "No costumes found.";
                } else {
                Costume::displayAllCostumes(*this);
                }
                break;
            }
            case 6: {
                int costumeID;
                cout << "======================================"<< endl;
                cout << "Enter costume ID: ";
                cin >> costumeID;
                cout << "======================================"<< endl;
                Costume::checkCostumeAvailability(*this, costumeID);
                break;
            }
            case 7: {
                int subChoice;
                cout << "======================================"<< endl;
                cout << "\nCustomer Maintenance Menu:\n";
                cout << "======================================"<< endl;
                cout << "1. Add New Customer\n";
                cout << "2. Show Customer Details\n";
                cout << "3. List All Costumes Rented by a Customer\n";
                cout << "======================================"<< endl;
                cout << "Enter your choice: ";
                cin >> subChoice;
                cout << "======================================"<< endl;

                switch (subChoice) {
                    case 1: {
                        int id;
                        string name, address;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> id;
                        cout << "Enter name: ";
                        cin.ignore(); // Ignore any remaining newline character in the buffer
                        getline(cin, name);
                        cout << "Enter address: ";
                        getline(cin, address);
                        cout << "======================================"<< endl;
                        Customer::addCustomer(*this, id, name, address);
                        break;
                    }
                    case 2: {
                        int customerID;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> customerID;
                        cout << "======================================"<< endl;
                        Customer::showCustomerDetails(*this, customerID);
                        break;
                    }
                    case 3: {
                        int customerID;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> customerID;
                        cout << "======================================"<< endl;
                        Customer::listAllCostumesRentedByCustomer(*this, customerID);
                        break;
                    }
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            }
            case 8: {
                cout << "Exiting program.\n";
                break;
            }
            default: {
                cout << "Invalid choice.\n";
            }
        }
    } while (choice != 8);
}

int main() {
    CostumeRental store;
    store.menu();
    return 0;
}
#include <iostream>
#include <fstream>
#include <string>
#include <deque>
#include <list>

using namespace std;

class CostumeRental; // Forward declaration

// Costume ADT
class Costume {
public:
    int costumeID;
    string costumeName;
    int size;
    string costumeFit;
    int numberOfCopies;

    Costume(int id, string n, int s, string f, int num)
        : costumeID(id), costumeName(n), size(s), costumeFit(f), numberOfCopies(num) {}

    void display() const {
        cout << "Costume ID: " << costumeID << "\nCostume Name: " << costumeName << "\nSize: " << size
             << "\nCostume Fit (Adult/Child): " << costumeFit << "\nNumber of Copies: " << numberOfCopies << endl;
    }

    static void addCostume(CostumeRental &store, int id, string costumeName, int size, string fit, int copies);
    static void rentCostume(CostumeRental &store, int customerID, int costumeID);
    static void returnCostume(CostumeRental &store, int customerID);
    static void showCostumeDetails(CostumeRental &store, int costumeID);
    static void displayAllCostumes(CostumeRental &store);
    static void checkCostumeAvailability(CostumeRental &store, int costumeID);
};

// Customer ADT
class Customer {
public:
    int customerID;
    string name;
    string address;

    Customer(int id, string n, string a)
        : customerID(id), name(n), address(a) {}

    void display() const {
        cout << "Customer ID: " << customerID << "\nName: " << name << "\nAddress: " << address << endl;
    }

    static void addCustomer(CostumeRental &store, int id, string name, string address);
    static void showCustomerDetails(CostumeRental &store, int customerID);
    static void listAllCustomers(CostumeRental &store);
    static void listAllCostumesRentedByCustomer(CostumeRental &store, int customerID);
};

// CustomerRent ADT (inherits from Customer)
class CustomerRent : public Customer {
public:
    list<int> rentedCostumes;

    CustomerRent(int id, string n, string a) : Customer(id, n, a) {}

    void rentCostume(int costumeID) {
        rentedCostumes.push_back(costumeID);
    }

    void returnCostume(int costumeID) {
        rentedCostumes.remove(costumeID);
    }

    void displayRentedCostumes() const {
        cout << "Costumes rented by Customer ID " << customerID << ":\n";
        for (list<int>::const_iterator it = rentedCostumes.begin(); it != rentedCostumes.end(); ++it) {
            cout << "Costume ID: " << *it << endl;
        }
    }

    void returnAllCostumes() {
        rentedCostumes.clear();
    }
};

// CostumeRental class to manage all operations
class CostumeRental {
private:
    deque<Costume> costumes;
    deque<CustomerRent> customers;
    int costumeCounter;
    int customerCounter;

public:
    CostumeRental() : costumeCounter(0), customerCounter(0) {
        loadCostumes();
        loadCustomers();
        loadCustomerRents();
    }

    void loadCostumes();
    void loadCustomers();
    void loadCustomerRents();
    void saveCostumes();
    void saveCustomers();
    void saveCustomersRents();
    void menu(); // Declare the menu function

    friend class Costume;
    friend class Customer;
};

// Costume ADT operations implementation
void Costume::addCostume(CostumeRental &store, int id, string costumeName, int size, string fit, int copies) {
    store.costumes.push_back(Costume(id, costumeName, size, fit, copies));
    store.saveCostumes();
    cout << "Costume added successfully.\n" << endl;
}

void Costume::rentCostume(CostumeRental &store, int customerID, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            if (it->numberOfCopies > 0) {
                it->numberOfCopies--;
                for (deque<CustomerRent>::iterator cit = store.customers.begin(); cit != store.customers.end(); ++cit) {
                    if (cit->customerID == customerID) {
                        cit->rentCostume(costumeID);
                        store.saveCostumes();
                        store.saveCustomersRents();
                        cout << "Costume rented successfully.\n" << endl;
                        return;
                    }
                }
                cout << "Customer not found.\n" << endl;
                return;
            } else {
                cout << "Costume not available.\n" << endl;
                return;
            }
        }
    }
    cout << "Costume not found.\n" << endl;
}

void Costume::returnCostume(CostumeRental &store, int customerID) {
    for (deque<CustomerRent>::iterator cit = store.customers.begin(); cit != store.customers.end(); ++cit) {
        if (cit->customerID == customerID) {
            cit->displayRentedCostumes();
            for (list<int>::iterator it = cit->rentedCostumes.begin(); it != cit->rentedCostumes.end(); ++it) {
                for (deque<Costume>::iterator vit = store.costumes.begin(); vit != store.costumes.end(); ++vit) {
                    if (vit->costumeID == *it) {
                        vit->numberOfCopies++;
                    }
                }
            }
            cit->returnAllCostumes();
            store.saveCostumes();
            store.saveCustomersRents();
            cout << "All costumes returned successfully.\n" << endl;
            return;
        }
    }
    cout << "Customer not found.\n" << endl;
}

void Costume::showCostumeDetails(CostumeRental &store, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            return;
        }
    }
    cout << "Costume with ID " << costumeID << " not found.\n" << endl;
}

void Costume::displayAllCostumes(CostumeRental &store) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        it->display();
        cout << endl;
    }
    
}

void Costume::checkCostumeAvailability(CostumeRental &store, int costumeID) {
    for (deque<Costume>::iterator it = store.costumes.begin(); it != store.costumes.end(); ++it) {
        if (it->costumeID == costumeID) {
            it->display();
            cout << "Number of copies available: " << it->numberOfCopies << "\n";
            if (it->numberOfCopies > 0) {
                cout << "Status: Available\n" << endl;
            } else {
                cout << "Status: Not Available\n" << endl;
            }
            return;
        }
    }
    cout << "Costume not found.\n" << endl;
}

// Customer ADT operations implementation
void Customer::addCustomer(CostumeRental &store, int id, string name, string address) {
    store.customers.push_back(CustomerRent(id, name, address));
    store.saveCustomers();
    cout << "Customer added successfully.\n" << endl;
}

void Customer::showCustomerDetails(CostumeRental &store, int customerID) {
    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        if (it->customerID == customerID) {
            it->display();
            return;
        }
    }
    cout << "Customer not found.\n" << endl;
}

void Customer::listAllCustomers(CostumeRental &store) {
    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        it->display();
        cout << endl;
    }
}

void Customer::listAllCostumesRentedByCustomer(CostumeRental &store, int customerID) {
    bool customerFound = false;

    for (deque<CustomerRent>::iterator it = store.customers.begin(); it != store.customers.end(); ++it) {
        if (it->customerID == customerID) {
            customerFound = true;
            if (it->rentedCostumes.empty()) {
                cout << "Customer ID " << customerID << " has not rented any costumes.\n" << endl;
            } else {
                it->displayRentedCostumes();
            }
            return;
        }
    }
    if (!customerFound) {
        cout << "Customer not found.\n" << endl;
    }
}

// CostumeRental class function implementations
void CostumeRental::loadCostumes() {
    ifstream inFile("costumes.txt");
    if (!inFile) {
        cerr << "Error opening costumes file.\n" << endl;
        return;
    }

    int id, size, copies;
    string costumeName, fit;
    while (inFile >> id) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, costumeName);
        inFile >> size;
        inFile.ignore(); // Ignore the newline character
        getline(inFile, fit);
        inFile >> copies;
        costumes.push_back(Costume(id, costumeName, size, fit, copies));
    }
    inFile.close();
}

void CostumeRental::loadCustomers() {
    ifstream inFile("customers.txt");
    if (!inFile) {
        cerr << "Error opening customers file.\n" << endl;
        return;
    }

    int id;
    string name, address;
    while (inFile >> id) {
        inFile.ignore(); // Ignore the newline character
        getline(inFile, name);
        getline(inFile, address);
        customers.push_back(CustomerRent(id, name, address));
    }
    inFile.close();
}

void CostumeRental::loadCustomerRents() {
    ifstream inFile("customer_rents.txt");
    if (!inFile) {
        cerr << "Error opening customer rents file.\n" << endl;
        return;
    }

    int customerID, costumeID;
    while (inFile >> customerID >> costumeID) {
        for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
            if (it->customerID == customerID) {
                it->rentCostume(costumeID);
                break;
            }
        }
    }
    inFile.close();
}

void CostumeRental::saveCostumes() {
    ofstream outFile("costumes.txt");
    if (!outFile) {
        cerr << "Error opening costumes file for writing.\n" << endl;
        return;
    }

    
    outFile << "Costumes Data File\n"; //labeling text for text file
    outFile << "ID | Name | Size | Fit | NumberOfCopies\n"; //labeling text for text file

    for (deque<Costume>::iterator it = costumes.begin(); it != costumes.end(); ++it) {
        outFile << it->costumeID << "  | " << it->costumeName << " | "
                << it->size << " | " << it->costumeFit << " | "
                << it->numberOfCopies << endl;
    }
    outFile.close();
}

void CostumeRental::saveCustomers() {
    ofstream outFile("customers.txt");
    if (!outFile) {
        cerr << "Error opening customers file for writing.\n" << endl;
        return;
    }

    
    outFile << "Customers Data File\n"; //labeling text for text file
    outFile << "ID | Name | Address\n"; //labeling text for text file

    for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
        outFile << it->customerID << "  | " << it->name << " | "
                << it->address << endl;
    }
    outFile.close();
}

void CostumeRental::saveCustomersRents() {
    ofstream outFile("customer_rents.txt");
    if (!outFile) {
        cerr << "Error opening customer rents file for writing.\n" << endl;
        return;
    }

    outFile << "Customer Rents Data File\n"; //labeling text for text file
    outFile << "CustomerID | CostumeID\n"; //labeling text for text file

    for (deque<CustomerRent>::iterator it = customers.begin(); it != customers.end(); ++it) {
        for (list<int>::iterator vit = it->rentedCostumes.begin(); vit != it->rentedCostumes.end(); ++vit) {
            outFile << it->customerID << " | " << *vit << endl;
        }
    }
    outFile.close();
}

void CostumeRental::menu() {
    int choice;
    do {
        cout << "======================================"<< endl;
        cout << "Costume Rental System Menu:\n";
        cout << "======================================"<< endl;
        cout << "1. New Costume\n";
        cout << "2. Rent a Costume\n";
        cout << "3. Return a Costume\n";
        cout << "4. Show Costume Details\n";
        cout << "5. Display All Costumes\n";
        cout << "6. Check Costume Availability\n";
        cout << "7. Customer Maintenance\n";
        cout << "8. Exit\n";
        cout << "======================================"<< endl;
        cout << "Enter your choice: ";
        cin >> choice;
        cout << "======================================"<< endl;

        switch (choice) {
            case 1: {
                int id;
                string costumeName;
                int size;
                string fit;
                int copies;
                cout << "Enter costume ID: ";
                cin >> id;
                cout << "Enter costume name: ";
                cin.ignore(); // Ignore any remaining newline character in the buffer
                getline(cin, costumeName);
                cout << "Enter size: ";
                cin >> size;
                cout << "Enter fit (Adult/Child): ";
                cin.ignore(); // Ignore any remaining newline character in the buffer
                getline(cin, fit);
                cout << "Enter number of copies: ";
                cin >> copies;
                Costume::addCostume(*this, id, costumeName, size, fit, copies);
                break;
            }
            case 2: {
                int customerID, costumeID;
                cout << "Enter customer ID: ";
                cin >> customerID;
                Customer::showCustomerDetails(*this, customerID);
                char rentAgain;
                do {
                    cout << "Enter costume ID: ";
                    cin >> costumeID;
                    Costume::rentCostume(*this, customerID, costumeID);
                    cout << "Do you want to rent another costume? (Y/N): ";
                    cin >> rentAgain;
                } while (rentAgain == 'Y' || rentAgain == 'y');
                break;
            }
            case 3: {
                int customerID;
                cout << "======================================"<< endl;
                cout << "Enter customer ID: ";
                cin >> customerID;
                cout << "======================================"<< endl;
                Costume::returnCostume(*this, customerID);
                break;
            }
            case 4: {
                int costumeID;
                cout << "======================================"<< endl;
                cout << "Enter costume ID: ";
                cin >> costumeID;
                Costume::showCostumeDetails(*this, costumeID); 
                break;
            }
            case 5: {
                if(costumes.empty()){
                    cout << "No costumes found.";
                } else {
                Costume::displayAllCostumes(*this);
                }
                break;
            }
            case 6: {
                int costumeID;
                cout << "======================================"<< endl;
                cout << "Enter costume ID: ";
                cin >> costumeID;
                cout << "======================================"<< endl;
                Costume::checkCostumeAvailability(*this, costumeID);
                break;
            }
            case 7: {
                int subChoice;
                cout << "======================================"<< endl;
                cout << "\nCustomer Maintenance Menu:\n";
                cout << "======================================"<< endl;
                cout << "1. Add New Customer\n";
                cout << "2. Show Customer Details\n";
                cout << "3. List All Costumes Rented by a Customer\n";
                cout << "======================================"<< endl;
                cout << "Enter your choice: ";
                cin >> subChoice;
                cout << "======================================"<< endl;

                switch (subChoice) {
                    case 1: {
                        int id;
                        string name, address;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> id;
                        cout << "Enter name: ";
                        cin.ignore(); // Ignore any remaining newline character in the buffer
                        getline(cin, name);
                        cout << "Enter address: ";
                        getline(cin, address);
                        cout << "======================================"<< endl;
                        Customer::addCustomer(*this, id, name, address);
                        break;
                    }
                    case 2: {
                        int customerID;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> customerID;
                        cout << "======================================"<< endl;
                        Customer::showCustomerDetails(*this, customerID);
                        break;
                    }
                    case 3: {
                        int customerID;
                        cout << "======================================"<< endl;
                        cout << "Enter customer ID: ";
                        cin >> customerID;
                        cout << "======================================"<< endl;
                        Customer::listAllCostumesRentedByCustomer(*this, customerID);
                        break;
                    }
                    default:
                        cout << "Invalid choice.\n";
                }
                break;
            }
            case 8: {
                cout << "Exiting program.\n";
                break;
            }
            default: {
                cout << "Invalid choice.\n";
            }
        }
    } while (choice != 8);
}

int main() {
    CostumeRental store;
    store.menu();
    return 0;
}
