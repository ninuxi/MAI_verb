#!/bin/bash
# Ad-hoc code signing for open source distribution
# No Apple Developer account required

set -e

# Colors
GREEN='\033[0;32m'
RED='\033[0;31m'
YELLOW='\033[1;33m'
NC='\033[0m'

echo -e "${GREEN}🔐 MAI_verb Ad-Hoc Code Signing${NC}"
echo "=================================="

# Find plugin paths
VST3_PATH=$(find BricastiM7_Clone/build -name "*.vst3" -type d 2>/dev/null | head -1)
AU_PATH=$(find BricastiM7_Clone/build -name "*.component" -type d 2>/dev/null | head -1)

if [ -z "$VST3_PATH" ] && [ -z "$AU_PATH" ]; then
    echo -e "${RED}❌ No plugins found! Build first with: cd BricastiM7_Clone && ./build_m7.sh${NC}"
    exit 1
fi

# Sign VST3
if [ -n "$VST3_PATH" ]; then
    echo -e "${YELLOW}Signing VST3...${NC}"
    codesign --deep --force --sign - \
        --options runtime \
        --identifier "com.aiforlive.MAI_verb" \
        --timestamp=none \
        "$VST3_PATH"
    
    echo -e "${GREEN}✅ VST3 signed: $VST3_PATH${NC}"
    
    # Verify
    codesign -dv "$VST3_PATH" 2>&1 | grep "Signature=adhoc" && \
        echo -e "${GREEN}   ✓ Verified (ad-hoc signature)${NC}"
fi

# Sign AU
if [ -n "$AU_PATH" ]; then
    echo -e "${YELLOW}Signing AU...${NC}"
    codesign --deep --force --sign - \
        --options runtime \
        --identifier "com.aiforlive.MAI_verb.component" \
        --timestamp=none \
        "$AU_PATH"
    
    echo -e "${GREEN}✅ AU signed: $AU_PATH${NC}"
    
    # Verify
    codesign -dv "$AU_PATH" 2>&1 | grep "Signature=adhoc" && \
        echo -e "${GREEN}   ✓ Verified (ad-hoc signature)${NC}"
fi

echo ""
echo -e "${GREEN}🎉 Signing complete!${NC}"
echo -e "${YELLOW}⚠️  Remember: Users must run 'xattr -cr' before installing${NC}"
echo -e "   See CODESIGN_FREE.md for distribution instructions"
