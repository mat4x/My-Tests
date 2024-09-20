import { SyntheticEvent } from "react";
import data_api, { Person } from "../utility/api-data";

const CreateUser = () => {
  function handleSubmit(event: SyntheticEvent) {
    data_api.add_new(new Person(10, "JKL", "Finance", ["teal"]));
    console.log(data_api.get_all());

    event.preventDefault();
    // const form = event.currentTarget;

    // form.target

    // onSubmitUsername(event.currentTarget.elements.usernameInput.value)

    // people.push();

    return;
  }
  return (
    <>
      <h1>Create User</h1>
      <form onSubmit={handleSubmit}>
        <div>
          <span style={{ display: "inline-block", width: 240 }}>
            Enter Name:{" "}
          </span>
          <input name="employee-name" type="text" />
        </div>

        <div>
          <span style={{ display: "inline-block", width: 240 }}>
            Select Department:{" "}
          </span>
          <select defaultValue="IT">
            <option value="IT">IT</option>
            <option value="HR">HR</option>
            <option value="Finance">Finance</option>
          </select>
        </div>

        <br />

        <button type="submit">Submit</button>
      </form>

      <div>
        <h3>Current users</h3>
        <ul>
          {data_api.get_all().map((person) => (
            <li key={person.id}>{person.name}</li>
          ))}
        </ul>
      </div>
    </>
  );
};

export default CreateUser;
