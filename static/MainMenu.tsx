/* eslint-disable @typescript-eslint/no-explicit-any */
import React from "react";

import DisplayData from "../components/DisplayData";
import data_api from "../utility/api-data";

const MainMenu = () => {
  const [slectedID, setslectedID] = React.useState(1);

  const all_users = data_api.get_all();
  const user_options = all_users.map((person) => (
    <option value={person.id} key={person.id}>
      {person.name}
    </option>
  ));

  return (
    <>
      <h1>People Data</h1>
      <div>
        <span style={{ marginRight: 100 }}>Select User</span>
        <select
          id="selection"
          defaultValue={all_users[0].id}
          onChange={(e: any) => setslectedID(parseInt(e.target.value))}
        >
          {user_options}
          <option value={-1}>Invalid</option> {/* Invalid user */}
        </select>
      </div>
      <br />
      <DisplayData id={slectedID} />
    </>
  );
};

export default MainMenu;
