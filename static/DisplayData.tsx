/*
 * Card-like widget that displays
 * the persons information based on the
 * "id" parameter passed.
 *
 * shows a fallabck widget if invalid "id".
 */

import { useParams } from "react-router-dom";

import data_api from "../utility/api-data";

interface PersonID {
  id?: number;
}

function DisplayData(props: PersonID) {
  // Choose url param.id or props.id
  const { id: idFromParams } = useParams();
  const id = props.id || parseInt(idFromParams || "invalid");

  /* TODO: Fetch data from sql */
  const personObj = data_api.get_as_id(id); // simulate fetch data

  // OLD implementation
  /* const personObj = people.find((person) => person.id == id); // simulate fetch data */

  // Fallback if not found
  if (personObj === undefined) {
    return <p>Invalid ID ( id={id} ) passed. </p>;
  }

  const listColors = personObj.colors.map((color, index) => (
    <li key={index}>
      <span
        style={{
          display: "inline-block",
          color: "white",
          width: "90%",
          background: color,
          paddingLeft: 10,
          marginBottom: 10,
          borderRadius: 10,
        }}
      >
        {color}
      </span>
    </li>
  ));

  return (
    <div className="details">
      <h2>User Information</h2>
      <p>ID: EMP-{personObj.id}</p>
      <p>Department: {personObj.department}</p>
      <p>Name: {personObj.name}</p>

      <h2>Favourite colors</h2>
      <ul>{listColors}</ul>
    </div>
  );
}

export default DisplayData;
