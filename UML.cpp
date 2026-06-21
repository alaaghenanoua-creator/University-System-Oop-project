/*

+--------------------------------------------------+
|                    Person                        |
+--------------------------------------------------+
| # id: int                                        |
| # Fullname: string                               |
+--------------------------------------------------+
| + Person(id:int, name:string)                    |
| + display() const : virtual void                 |
| + ~Person() : virtual                            |
+--------------------------------------------------+
         ▲
         |
+--------------------------------------------------+
|                    Student                       |
+--------------------------------------------------+
| - academicYear: int                              |
+--------------------------------------------------+
| + Student(id:int, name:string, year:int)         |
| + getId() const : int                            |
| + storeinfo(id:int, name:string, year:int): void |
| + display() const : override void                |
| + getfullname() const : string                   |
| + save(out:ofstream&) : void                     |
| + getAcademicYear() const : int                  |
| + operator==(const Student& other) : bool        |
| + operator<<(out:ostream&, s:const Student&)     |
+--------------------------------------------------+

+--------------------------------------------------+
|                    Room                          |
+--------------------------------------------------+
| - roomNumber : int                               |
| - capacity : int                                 |
| - students : vector<Student*>                    |
| - actualNumber : int                             |
+--------------------------------------------------+
| + Room(n:int, c:int)                             |
| + addStudent(s:Student*) : bool                  |
| + displayRoom() const : void                     |
| + removeStudent(studentId:int) : bool            |
| + isFull() const : bool                          |
| + searchStudent(studentId:int) const : Student*  |
| + number_of_students() const : int               |
| + getroomNumber() const : int                    |
| + getCapacity() const : int                      |
| + getStudents() const : vector<Student*>&        |
+--------------------------------------------------+

+--------------------------------------------------+
|                  Restaurant                      |
+--------------------------------------------------+
| - breakfast : string                             |
| - lunch : string                                 |
| - dinner : string                                |
+--------------------------------------------------+
| + Restaurant(b:string, l:string, d:string)       |
| + setbreakfast(b:string): void                   |
| + setlunch(l:string): void                       |
| + setdinner(d:string): void                      |
| + display() const : void                         |
| + save(out:ofstream&) const : void               |
| + getBreakfast() const : string                  |
| + getLunch() const : string                      |
| + getDinner() const : string                     |
+--------------------------------------------------+

+-------------------------------------------------------+
|                   Dormitory                           |
+-------------------------------------------------------+
| - name : string                                       |
| - capacity : int                                      |
| - rooms : vector<Room>                                |
| - restaurant : Restaurant                             |
| - tookenRooms : int                                   |
+-------------------------------------------------------+
| + Dormitory(name:string, capacity:int,                |
|            restaurant:const Restaurant&)              |  
| + addRoom(r:const Room&) : void                       |  
| + assignStudent(s:Student*) : bool                    |    
| + removeStudent(studentId:int) : bool                 |  
| + displayAvailableRooms() const : void                |   
| + searchStudent_in_dormitory(studentId:int):Student*  |
| + getRoomCount() const : int                          |
| + getname() const : string                            |
| + getCapacity() const : int                           |
| + count_number_of_students_in_dor() const : int       |
| + saveRooms(out:ofstream&) const : void               |
| + savedorms(out:ofstream&) : void                     |
| + saveAssignments(out:ofstream&,                      |
|            dormName:const string&) const : void       |
| + assignStudentToRoom(s:Student*, roomNumber:int):bool|
| + saveRestaurant(out:ofstream&) const : void          |
| + setRestaurantMenu(breakfast:string,                 |
|            lunch:string, dinner:string) : void        |
| + showRestaurantMenu() const : void                   |
| + roomExists(roomNumber:int) const : bool             |
| + removeRoom(roomNumber:int) : bool                   |
+-------------------------------------------------------+

+--------------------------------------------------+
|                   University                     |
+--------------------------------------------------+
| - dormitories : vector<Dormitory>                |
| - students : vector<Student>                     |
+--------------------------------------------------+
| + addDormitory(const Dormitory&) : void          |
| + removeDormitory(const string&) : bool          |
| + search_Student(studentId:int) : Student*       |
| + getTotalDormitories() const : int              |
| + getTotalRooms() const : int                    |
| + getTotalStudents() const : int                 |
| + displayStatistics() const : void               |
| + addStudent(id:int, name:string, year:int): void|
| + assignStudentToDormitory(id:int,               |
|            dormName:const string&) : bool        |
| + saveAssignments(out:ofstream&) : void          |
| + loadStudents() : void                          |
| + loadDormitories() : void                       |
| + loadRooms() : void                             |
| + loadAssignments() : void                       |
| + loadAll() : void                               |
| + saveAll() : void                               |
| + saveStudents(out:ofstream&) : void             |
| + saveDormitories(out:ofstream&) : void          |
| + saveRooms(out:ofstream&) : void                |
| + removeStudent(studentId:int) : bool            |
| + saveRestaurants(out:ofstream&) : void          |
| + loadRestaurants() : void                       |
| + findById<T>(vec:vector<T>&, id:int) : T*       |
| + addRoomToDormitory(dormName:const string&,     |
|            roomNumber:int, capacity:int) : bool  |
| + assignStudentToRoom(studentId:int,             |
|   dormName:const string&, roomNumber:int) : bool |
| + removeRoomFromDormitory(dormName:const string&,|
|            roomNumber:int) : bool                |
+--------------------------------------------------+

University ♦────────── 0..* Dormitory (Composition)
University ♦────────── 0..* Student (Composition)
Dormitory ♦────────── 0..* Room (Composition)
Dormitory ♦────────── 1 Restaurant (Composition)
Room ◇────────── 0..* Student (Aggregation)
Person ▲────────── Student (Inheritance)


*/