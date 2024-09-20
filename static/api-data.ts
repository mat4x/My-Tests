// import React from "react";

export class Person {
  id: number = 0;
  name: string = "NA";
  department: string = "NA";
  colors: Array<string> = [];

  constructor(
    id: number,
    name: string,
    department: string,
    colors: Array<string>
  ) {
    this.id = id;
    this.name = name;
    this.department = department;
    this.colors = colors;
  }
}

// simulating sql calls
export class ApiHandler {
  /*
   * Implemented as a singleton class
   * Simulating data fetching; for now.
   *
   * TODO: use mySQL / sqlite3
   */

  private constructor() {}
  static #instance: ApiHandler;

  public static get instance(): ApiHandler {
    if (!ApiHandler.#instance) {
      ApiHandler.#instance = new ApiHandler();
      console.log("NEW API INSTANCE CREATED");
    }

    return ApiHandler.#instance;
  }

  data = [
    new Person(1, "ABC", "IT", ["red", "green", "blue"]),
    new Person(2, "DEF", "IT", ["yellow", "orange", "red", "pink"]),
    new Person(3, "XYZ", "Finance", ["grey", "black"]),
    new Person(4, "MNO", "HR", ["lightgreen", "green", "darkgreen"]),
  ];

  add_new(user: Person) {
    this.data.push(user);
  }

  // return all records array
  get_all() {
    return this.data;
  }

  // returns 1 record based on 'id' parameter
  get_as_id(id: number) {
    console.log(`Fetching user for ID = ${id}, ${typeof id}`);
    for (let i = 0; i < this.data.length; i++) {
      const person = this.data[i];
      if (person.id === id) {
        return person;
      }
    }
    return undefined;
  }

  // returns all users in the 'dept' department
  get_as_dept(dept?: string) {
    const user_in_dept: Person[] = [];

    if (dept === undefined) return null;

    for (let i = 0; i < this.data.length; i++) {
      const person = this.data[i];
      if (person.department === dept) {
        user_in_dept.push(person);
      }
    }

    return user_in_dept;
  }
}

const data_api = ApiHandler.instance;

data_api.add_new(new Person(5, "WASD", "Finance", ["red", "darkred"]));

// console.log("API", data_api.get_as_dept("HR"));

export default data_api;

// OLD implementation
/*
const people = [
  {
    id: 1,
    department: "IT",
    name: "ABC",
    colors: ["red", "green", "blue"],
  },
  {
    id: 2,
    department: "IT",
    name: "DEF",
    colors: ["yellow", "orange", "red", "pink"],
  },
  {
    id: 3,
    department: "HR",
    name: "MNO",
    colors: ["light green", "green", "dark green"],
  },
  {
    id: 4,
    department: "Finance",
    name: "XYZ",
    colors: ["white", "black"],
  },
];

export default people;
*/
