import data_api from "../utility/api-data";
import DisplayData from "../components/DisplayData";
import { useParams } from "react-router-dom";

export default function Department() {
  const { dept: dept } = useParams();

  // OLD fetching implementation
  /*
  const dept_people = people.filter(
    (person) => person.department.toLowerCase() == dept!.toLowerCase()
  );
  */

  // fetch data
  const dept_people = data_api.get_as_dept(dept);

  // Fallback if not found
  if (dept_people === undefined) {
    return <p>No user records found for "{dept}" department</p>;
  }

  const all_cards = dept_people!.map((person, index) => (
    <div key={index}>
      <DisplayData id={person.id} />
    </div>
  ));
  return (
    <>
      <h1>People in {dept} department</h1>
      {all_cards}
    </>
  );
}
