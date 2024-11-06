function solveTriangleASS(angleA, sideA, sideB) {
    const angleAInDegrees = angleA;
    const sideOppositeAngleA = sideA;
    const sideB = sideB;

    const rad = (deg) => deg * (Math.PI / 180);
    const deg = (rad) => rad * (180 / Math.PI);

    const cosAngleA = Math.cos(rad(angleAInDegrees));
    const sideBCosAngleA = sideB * cosAngleA;
    const discriminant = sideBCosAngleA * sideBCosAngleA - sideB * sideB + sideOppositeAngleA * sideOppositeAngleA;

    let sideC1, sideC2;
    if (discriminant < 0) {
        sideC1 = -1;
        sideC2 = -1;
    } else {
        sideC1 = sideBCosAngleA - Math.sqrt(discriminant);
        sideC2 = sideBCosAngleA + Math.sqrt(discriminant);
    }

    if (sideC1 > 0 && sideC2 > 0) {
        const angleB1 = deg(Math.acos((sideC1 * sideC1 + sideOppositeAngleA * sideOppositeAngleA - sideB * sideB) / (2 * sideC1 * sideOppositeAngleA)));
        const angleB2 = deg(Math.acos((sideC2 * sideC2 + sideOppositeAngleA * sideOppositeAngleA - sideB * sideB) / (2 * sideC2 * sideOppositeAngleA)));
        const angleC1 = deg(Math.acos((sideOppositeAngleA * sideOppositeAngleA + sideB * sideB - sideC1 * sideC1) / (2 * sideOppositeAngleA * sideB)));
        const angleC2 = deg(Math.acos((sideOppositeAngleA * sideOppositeAngleA + sideB * sideB - sideC2 * sideC2) / (2 * sideOppositeAngleA * sideB)));

        const semiPerimeter1 = (sideOppositeAngleA + sideB + sideC1) / 2;
        const semiPerimeter2 = (sideOppositeAngleA + sideB + sideC2) / 2;

        const area1 = Math.sqrt(semiPerimeter1 * (semiPerimeter1 - sideOppositeAngleA) * (semiPerimeter1 - sideB) * (semiPerimeter1 - sideC1));
        const area2 = Math.sqrt(semiPerimeter2 * (semiPerimeter2 - sideOppositeAngleA) * (semiPerimeter2 - sideB) * (semiPerimeter2 - sideC2));

        const perimeter1 = sideOppositeAngleA + sideB + sideC1;
        const perimeter2 = sideOppositeAngleA + sideB + sideC2;

        console.log("SIDE(C1): " + sideC1);
        console.log("ANGLE(B1): " + angleB1);
        console.log("ANGLE(C1): " + angleC1);
        console.log("PERIMETER(1): " + perimeter1);
        console.log("AREA(1): " + area1);

        console.log("SIDE(C2): " + sideC2);
        console.log("ANGLE(B2): " + angleB2);
        console.log("ANGLE(C2): " + angleC2);
        console.log("PERIMETER(2): " + perimeter2);
        console.log("AREA(2): " + area2);
    } else if (sideC1 > 0) {
        const angleB1 = deg(Math.acos((sideC1 * sideC1 + sideOppositeAngleA * sideOppositeAngleA - sideB * sideB) / (2 * sideC1 * sideOppositeAngleA)));
        const angleC1 = deg(Math.acos((sideOppositeAngleA * sideOppositeAngleA + sideB * sideB - sideC1 * sideC1) / (2 * sideOppositeAngleA * sideB)));

        const semiPerimeter1 = (sideOppositeAngleA + sideB + sideC1) / 2;
        const area1 = Math.sqrt(semiPerimeter1 * (semiPerimeter1 - sideOppositeAngleA) * (semiPerimeter1 - sideB) * (semiPerimeter1 - sideC1));
        const perimeter1 = sideOppositeAngleA + sideB + sideC1;

        console.log("SIDE(C): " + sideC1);
        console.log("ANGLE(B): " + angleB1);
        console.log("ANGLE(C): " + angleC1);
        console.log("PERIMETER: " + perimeter1);
        console.log("AREA: " + area1);
    } else if (sideC2 > 0) {
        const angleB2 = deg(Math.acos((sideC2 * sideC2 + sideOppositeAngleA * sideOppositeAngleA - sideB * sideB) / (2 * sideC2 * sideOppositeAngleA)));
        const angleC2 = deg(Math.acos((sideOppositeAngleA * sideOppositeAngleA + sideB * sideB - sideC2 * sideC2) / (2 * sideOppositeAngleA * sideB)));

        const semiPerimeter2 = (sideOppositeAngleA + sideB + sideC2) / 2;
        const area2 = Math.sqrt(semiPerimeter2 * (semiPerimeter2 - sideOppositeAngleA) * (semiPerimeter2 - sideB) * (semiPerimeter2 - sideC2));
        const perimeter2 = sideOppositeAngleA + sideB + sideC2;

        console.log("SIDE(C): " + sideC2);
        console.log("ANGLE(B): " + angleB2);
        console.log("ANGLE(C): " + angleC2);
        console.log("PERIMETER: " + perimeter2);
        console.log("AREA: " + area2);
    } else {
        console.log("TRIANGLE DOES NOT EXIST");
    }
}

// Example usage:
solveTriangleASS(30, 5, 7);